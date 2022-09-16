#include "ast.hpp"

#include "assert.hpp"

unsigned ast_node_t::num_children() const
{
    using namespace lex;

    switch(token.type)
    {
    case TOK_apply:
    case TOK_cast:
    case TOK_byte_block_proc:
    case TOK_byte_block_data:
        assert(!token.value || children);
        return token.value;

    case TOK_at:
    case TOK_unary_plus:
    case TOK_unary_minus:
    case TOK_unary_xor:
    case TOK_unary_negate:
    case TOK_unary_ref:
    case TOK_sizeof_expr:
    case TOK_len_expr:
    case TOK_period:
    case TOK_read_hw:
        assert(children);
        return 1;

    case TOK_byte_block_asm_op:
        return children ? 1 : 0;

    case TOK_write_hw:
    case TOK_index8:
    case TOK_index16:
        return 2;

    default:
        if(is_operator(token.type))
        {
            assert(children);
            return 2;
        }

        passert(!children, token_string(token.type));
        // fall-through
        // These use other pointers in the union instead of 'children':
    case TOK_byte_block_call:
    case TOK_byte_block_goto:
    case TOK_byte_block_goto_mode:
    case TOK_character:
    case TOK_string_compressed:
    case TOK_string_uncompressed:
        return 0;
    }
}