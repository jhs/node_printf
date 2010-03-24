var binding = require("./binding"),
    sys     = require('sys');

var Printf = new binding.Printf;

exports.sprintf = function() {
  sys.puts("printf.js sprintf: " + sys.inspect(arguments));
  return Printf.sprintf(Array.prototype.slice.call(arguments));
};
