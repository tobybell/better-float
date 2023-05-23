# Better Float

A 64-bit floating point format with the following properties:

* Can represent all finite IEEE 754 double-precision values
* No distinction between -0 and +0 (same representation)
* No representation for infinity or NaN
* Monotonic when interpretted as a signed 64-bit integer
* Follows 2's complement when interpretted as a signed 64-bit integer (you can
  negate a float by negating its integer representation)

Because this representation cannot represent infinity or NaN, its range of
finite values extends slightly further than the usual IEEE 754 range, to
`±3.5953862697246318e+308`.

## License

This software is unlicensed. You may not use, modify, or distribute it without
my permission.
