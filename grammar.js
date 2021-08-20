module.exports = grammar({
  name: 'test',

  rules: {
    source_file: $ => token(repeat1(seq('a', '\0')))
  }
});
