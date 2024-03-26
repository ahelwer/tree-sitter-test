use tree_sitter::{Parser, Query, QueryCursor};

fn main() {
    let mut parser = Parser::new();
    parser.set_language(&tree_sitter_test::language()).expect("Error loading grammar");
    let source_code = "op == expr op ≜ expr";
    let tree = parser.parse(source_code, None).unwrap();
    println!("{}", tree.root_node().to_sexp());

    let query = Query::new(&tree_sitter_test::language(), "(def_eq \"≜\" @def_eq)").unwrap();
    let mut cursor = QueryCursor::new();
    for capture in cursor.matches(&query, tree.root_node(), "".as_bytes()) {
        println!("{:?}", capture);
    }
}
