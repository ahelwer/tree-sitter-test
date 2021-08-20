module.exports = grammar({
  name: 'test',
  
  externals: $ => [
    $.token
  ],

  rules: {
    source_file: $ => repeat1($.token)
  }
});
