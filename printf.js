var binding = require("./binding"),
    sys     = require('sys');

var Printf = new binding.Printf;

exports.sprintf = function(format) {
  sys.puts('sprintf with ' + sys.inspect(format));
  //return p.sprintf(format);
  return Printf.sprintf(format);
};
