import XCTest
import SwiftTreeSitter
import TreeSitterJinja

final class TreeSitterJinjaTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_jinja())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Jinja grammar")
    }
}
