#include "../../include/lifter/ir.h"

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

void build_cfg(IRContext* ctx) {
    // End basic block when:
    //
}