#include "../../include/lifter/ir.h"
#define END 0xFF

void create_ir_context(IRContext* ctx) {
    // root will be set dynamically, since ast_node constructor will malloc for us.
    ctx->state_map = malloc(sizeof(DynamicArray));
    ctx->side_effects = malloc(sizeof(DynamicArray));
    init_dynamic_array(ctx->state_map, 40, sizeof(StateMapEntry));
    init_dynamic_array(ctx->side_effects, 40, sizeof(ast_node_t*));
}

void free_ir_context(IRContext *ctx){
    free_dynamic_array(ctx->state_map);
    free_dynamic_array(ctx->side_effects);
    free(ctx->state_map);
    free(ctx->side_effects);
}


ast_node_t* get_current_state(IRContext* ctx, uint32_t memory_addr){
    StateMapEntry* entries = (StateMapEntry*)ctx->state_map->data;

    for(int i = 0; i < ctx->state_map->size; i++){
        if(entries[i].address == memory_addr){
            return (ast_node_t*) entries[i].node;
        }
    }
    // No node is found here, so we need to construct a new node to hold the value
    ast_node_t* node = make_node(OPCODE_MEMORY_ADDRESS, NULL, NULL, NULL, memory_addr);

    return node;
}
void set_current_state(IRContext* ctx, uint32_t memory_addr, ast_node_t* node){
    StateMapEntry* entries = (StateMapEntry*)ctx->state_map->data;

    for(int i = 0; i < ctx->state_map->size; i++){

        if(entries[i].address == memory_addr){
            entries[i].node = node;
            return;
        }
    }

    //We didn't find the address exists yet, so we initialize a new entry

    StateMapEntry entry = {.address = memory_addr, .node = node};
    push_back(ctx->state_map, &entry);
}

// Helper function to find the array index of a given memory address
int find_index_by_addr(DynamicArray* disassembly, uint32_t target_addr) {
    for(size_t i = 0; i < disassembly->size; i++) {
        DecodedInstr* instr = (DecodedInstr*)get(disassembly, i);
        if(instr->mem_addr == target_addr) {
            return i; // Return the array index
        }
    }
    return -1; // Not found
}

DynamicArray* build_cfg(IRContext* ctx, DynamicArray* disassembly) {
    DynamicArray* basic_blocks = malloc(sizeof(DynamicArray));
    init_dynamic_array(basic_blocks, 40, sizeof(BasicBlock));

    if (disassembly->size == 0) return basic_blocks;

    // Allocate an array of booleans parallel to the instructions array
    bool* is_leader = calloc(disassembly->size, sizeof(bool));

    // The first instruction is always a leader
    is_leader[0] = true;

    // Pass 1: Identify leaders
    for(size_t i = 0; i < disassembly->size; i++) {
        DecodedInstr* instr = (DecodedInstr*)get(disassembly, i);
        if(!instr->is_binary && instr->opcode != END) continue;
        // The target of a direct jump is a leader
        if(instr->opcode == 16 || instr->opcode == 18) {
            int target_idx = find_index_by_addr(disassembly, instr->op_b);
            if (target_idx != -1) {
                is_leader[target_idx] = true;
            }
        }
        else if (instr->opcode == 0 && instr->op_a == 0) {
            //conditionless jump, move ip to immediate
            int target_idx = find_index_by_addr(disassembly, instr->op_b);
            if (target_idx != -1) {
                is_leader[target_idx] = true;
            }
        }
        //after any jmp or move to [0], the target is a leader
        bool is_jmp_to_ip = (instr->opcode <= 5) && (instr->op_a == 0);
        if((instr->opcode >= 16 && instr->opcode <= 19) || instr->opcode == END || is_jmp_to_ip) {
            if (i + 1 < disassembly->size) is_leader[i + 1] = true;
        }

        // The instruction immediately following any jump or halt is a leader
        if((instr->opcode >= 16 && instr->opcode <= 19) || instr->opcode == END || is_jmp_to_ip) {
            if (i + 1 < disassembly->size) {
                is_leader[i + 1] = true;
            }
        }
    }

    // 2nd Pass: Chunk the Blocks
    BasicBlock current_block = {0};
    current_block.start_idx = 0;
    current_block.start_addr = ((DecodedInstr*)get(disassembly, 0))->mem_addr;

    for(size_t i = 0; i < disassembly->size; i++) {
        DecodedInstr* instr = (DecodedInstr*)get(disassembly, i);

        // If we hit a leader, AND we aren't still on the first instruction of the current block
        if (is_leader[i] && i > current_block.start_idx && instr->opcode != END) {

            // Close the current block on the PREVIOUS instruction
            current_block.end_idx = i - 1;
            push_back(basic_blocks, &current_block);

            // Start a new block
            current_block = (BasicBlock){0};
            current_block.start_idx = i;
            current_block.start_addr = instr->mem_addr;
        }

        // If we are at the very last instruction of the file, we must close the final block
        if (i == disassembly->size - 1) {
            current_block.end_idx = i;
            push_back(basic_blocks, &current_block);
        }
    }

    free(is_leader); // Clean up the temporary array
    return basic_blocks;
}

void link_cfg_edges(DynamicArray* basic_blocks, DynamicArray* disassembly) {
    for(int i = 0; i < basic_blocks->size; i++) {
        BasicBlock* block = get(basic_blocks, i);


        init_dynamic_array(block->successors, 2, sizeof(BasicBlock*));
        init_dynamic_array(block->predecessors, 4, sizeof(BasicBlock*));

        DecodedInstr terminator = ((DecodedInstr*)disassembly->data)[block->end_idx];
        if(terminator.opcode == END) {
            // No successors
            continue;
        }
        // conditional jump fail
        if(i + 1 < basic_blocks->size) {
            BasicBlock* successor = (BasicBlock*)basic_blocks->data + i + 1;
            push_back(block->successors, &successor);
            push_back(successor->predecessors, &block);
        }
        // conditional jump success
        // we grab the constant memory value and see if it exists in our basic blocks
        for(int j = 0; j < basic_blocks->size; j++) {
            BasicBlock* successor = (BasicBlock*)basic_blocks->data + j;
            if(successor->start_addr == terminator.op_b) {
                push_back(block->successors, &successor);
                push_back(successor->predecessors, &block);
                break;
            }
        }
    }
}
