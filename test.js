var sys = require('sys'),
    puts = sys.puts,
    printf = require('./printf');

puts("process.argv " + sys.inspect(process.argv.slice(2)));
puts("sprintf says: ");
puts(printf.sprintf.apply(printf.sprintf, process.argv.slice(2)));
