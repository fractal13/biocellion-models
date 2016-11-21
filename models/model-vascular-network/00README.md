To use this, edit RUN.bash to set the location of your
Biocellion installation.  Then, use `./RUN.bash`.  This
will copy the model into place, build the code, run the
simulation, and store the output in `output`.

This model has a single diffusive value "nutrient".  At the
beginning, the volume is initialized with the center UB
having an amount of 100.  At the start of every state-and-grid
timestep, another 10 units are added to the center UB.  Meanwhile,
a PDE solver is used to diffuse the nutrient to other cells.

Default parameters takes about 6 seconds to run on my
Intel(R) Core(TM) i3-2330M CPU @ 2.20GHz with effectively
4 cores.

In Paraview, you have to select each of the .vti file groups
separately.  There is one group per partition, and there are
8 partitions in the default configuration.  I actually just
selected one for viewing, since the simulation is symmetric,
viewing any one of the 8 is effective to see the result.

Select the .vti group(s).

I usually do "reset view", followed by "Set view direction to +Z".

For each .vti group(s), add a Slice.  Configure the slice to
have "phi" for Coloring, and set the view plane (to start, I
put "Camera Normal" and "Center on Boundary".  Apply.

You should be able to watch the concentration spread out from
the center.

