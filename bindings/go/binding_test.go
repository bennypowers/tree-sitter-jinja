package tree_sitter_jinja_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_jinja "github.com/bennypowers/tree-sitter-jinja/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_jinja.Language())
	if language == nil {
		t.Errorf("Error loading Jinja grammar")
	}
}
