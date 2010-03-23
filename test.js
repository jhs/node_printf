var sys = require('sys'),
    puts = sys.puts,
    printf = require('./printf');

puts("sprintf says: ");
puts(printf.sprintf("%d", 23));
