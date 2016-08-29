# timermath.h
This is a C header library for dealing with timer rollover math. This header implements the essential functions for comparing timer values, taking the difference between timer values, and incrementing / decrementing timer values.

These functions are designed for timers that increment form 0 and roll back over to 0 after reaching a fixed maximum value. This library will also handle timer values that roll over on non (2**n -1) boundaries.

## Installation
The [timermath.h](src/timermath/timermath.h) header may be copied directly into your project, or it can be installed into your project with [clib](https://github.com/clibs/clib):

```
$ clib install bradschl/timermath.h
```

## Example
```C
 /**
  * For a 3 bit timer that starts at 0 and increments to 7
  * 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, ......
  */

 struct tm_math tm;
 tm_initialize(&tm, 0x07);
 
 tm_get_diff(&tm, 0, 7);  // (0 - 7) == 1
 tm_get_diff(&tm, 4, 6);  // (4 - 6) == -2
 tm_is_gt(&tm, 0, 7);     // (0 > 7) == true
 tm_is_le(&tm, 2, 5);     // (2 <= 5) == true

 uint32_t t = tm_offset(&tm, 2, 1); // (2 + 1) == 3
 t = tm_offset(&tm, t, -2); // (3 - 2) == 1
 // ...
```

## License
MIT license for all files.
