# tree-sitter-jinja-dialects

A [tree-sitter](https://tree-sitter.github.io/) grammar for the Jinja template
language family.

## Supported languages

This grammar parses the **union** of syntax from:

- **Jinja2** (Python) - the original
- **Nunjucks** (JavaScript) - Mozilla's JS port, used by 11ty
- **Twig** (PHP) - Symfony's template engine
- **Tera** (Rust) - Rust port
- **Inja** (C++) - C++ port
- **Django Templates** (Python) - predecessor, subset syntax

Valid syntax from any of these languages is accepted. Both `true` and `True`
parse as booleans; both `none` and `null` parse as null literals; both
`key=val` and `key: val` work in keyword arguments.

## Architecture

The grammar follows a **template-first** approach: it parses template
delimiters and structure, exposing `text` nodes for HTML injection via
`queries/injections.scm`.

```
source_file := repeat(choice(statement, output, comment, text))
```

### Expressions

Full expression parsing with 13-level precedence, including:

- Arithmetic, comparison, logical, membership (`in`/`not in`), identity (`is`/`is not`)
- Filter chains (`x | lower | truncate(50)`)
- Member access (`obj.prop`, `obj?.prop`), subscript (`items[0]`)
- Function calls with keyword arguments and spread
- Conditional expressions (Jinja2 `x if c else y` and Twig `c ? x : y`)
- Twig operators: `===`, `!==`, `??`, `b-and`/`b-or`/`b-xor`

### Statements

All standard block and inline statements:

- `if`/`elif`/`else`/`endif`
- `for`/`else`/`endfor` (with tuple unpacking, condition filter, `recursive`)
- `block`/`endblock`, `macro`/`endmacro`, `call`/`endcall`
- `filter`/`endfilter`, `with`/`endwith`, `autoescape`/`endautoescape`
- `raw`/`endraw` and `verbatim`/`endverbatim` (via external scanner)
- `set` (inline and block forms), `extends`, `include`, `import`, `from`, `do`
- Catch-all `generic_tag` for custom/extension tags

### Whitespace control

All delimiter pairs support `-` (strip) and `~` (Twig preserve-newlines):

```
{{- expr -}}    {%- tag -%}    {#- comment -#}
{{~ expr ~}}    {%~ tag ~%}    {#~ comment ~#}
```

## Queries

| File | Purpose |
|------|---------|
| `highlights.scm` | Syntax highlighting |
| `injections.scm` | HTML injection into `text` nodes |
| `locals.scm` | Variable definitions and references |
| `tags.scm` | Symbol tagging (blocks, macros) |

## Usage

### Neovim

```lua
-- In your tree-sitter config
require('nvim-treesitter.configs').setup {
  ensure_installed = { 'jinja' },
}
```

### Node.js

```js
const Parser = require('tree-sitter');
const Jinja = require('tree-sitter-jinja-dialects');

const parser = new Parser();
parser.setLanguage(Jinja);

const tree = parser.parse('{{ name | lower }}');
```

## Bindings

Pre-built bindings for C, Go, Node.js, Python, Rust, and Swift.

## License

MIT
