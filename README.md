# Taylor-Calculator
Scientific Calculator Application
Implements common methods found on scientific calculators using Taylor series.

The methods used in this project are fundamental functions, such as a factorial function, as well as
trigonometric functions, exponential and natural logarithmic.

The project needs no outside data, all important constants are stored internally. The sine, cosine,
and tangent functions were tested with several values, including values from all four quadrants of
the cartesian plane. If those functions worked, it means the cosecant, secant, and cotangent
functions would work, since they're implemented using ratio identities of sine and cosine functions.
The sine and cosine functions will be the only trigononmetric functions with Taylor series'.

The calculator is unable to calculate for extremely large or small numbers due to the minimum
and maximum values allowed by a double type and the precision of 10^-12, which exists for a
reasonable runtime.
