# Sheep's Suckless Programs

A collection of my [suckless](https://suckless.org/) programs, along with my personal configuration changes and patches.

## Installation
See the `README` files within the folders of your desired program(s) to see how to install them.

You may also consult the [suckless website](https://suckless.org/) for more information.

## Configuration
All suckless programs are configured via `patches`.

In particular, these patches are nothing but the outputs of `git diff` made by the developer(s) of the patch.

### Patching
Patches for suckless programs can be found on their [website](https://suckless.org/).

e.g., `dwm` patches are found in: https://dwm.suckless.org/patches/

> To add a patch to a suckless program, first:

1. Change your current working directory to the root directory of the suckless program to be patched.

e.g., if patching `dwm`:
```bash
cd path/to/dwm-dir
```

2. Apply the patch.
```bash
# Assuming your patch is in the `patches/` directory.
patch -i patches/<my-dwm-patch>.diff
```

3. Fix parts of the patch (if necessary).

Some [hunks](https://www.gnu.org/software/diffutils/manual/html_node/Hunks.html) may not be administered correctly when applying patches.
Denoted by messages of the form: `Hunk failed at...`

In such cases, manual user intervention is required.

Take a look at all `.rej` files to see which lines failed to be applied and apply them manually to the corresponding files.

## Notes
`statuscmd` is not currently set up between `dwm` and `dwmblocks`.

That is because it is not configured.

I plan to re-patch `dwm` from the ground-up so that it will work well with `dwmblocks` in the future.

