To use this, edit RUN.bash to set the location of your
Biocellion installation.  Then, use `./RUN.bash`.  This
will copy the model into place, build the code, run the
simulation, and store the output in `output`.

This model puts a single cell in the center of the domain,
then applies a 10% growth rate to its mass every time step.
When the mass reaches 200% of the minimum mass of a cell,
the cell splits in half.  The radius of the cell is updated
based on a fixed density and the varying mass.

Default parameters takes about 25 seconds to run on my
Intel(R) Core(TM) i3-2330M CPU @ 2.20GHz with effectively
4 cores.

In Paraview, set the Glyph viewing properties to be:
Scalars: radius
Glyph Type: Sphere
Radius: 1
Scale Mode: scalar
Set Scale Factor: 1
Coloring: radius

You should be able to watch the cells divide and jostle
for position.




