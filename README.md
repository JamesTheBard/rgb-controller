# Commands

| Command | Format | Comment |
|:-:|:--|:--|
| `all` | `allPRGB` | Set all of the LEDs on a port to the same color. `P` is the port, `RGB` is the color to set it as. |
| `pix` | `setPXXRGB` | Set a pixel on a given port to a given color. `P` is the port, `XX` is the pixel in hex, and `RGB` is the color to set it to. |
| `rng` | `rngPXXYYRGB` | Set a set of pixels on a given port to a color. `P` is the port, `XX` is the starting pixel, `YY` is the ending pixel, and `RGB` is the color to set them to. |
| `gra` | `graPXXYYRGBRGB` | Set a gradient start with pixel `XX` and ending with `YY`.  The gradient color starts with the first `RGB` color and ends with the second `RGB` color. |
| `bri` | `briBB` | Set the brightness to `BB`. |
| `sho` | `sho` | Apply changes to the LEDs. |
| `sav` | `sav` | Save settings/state to flash. |
| `loa` | `loa` | Load settings/state from flash. |
| `log` | `logX` | Set the verbosity of the output.  `1` is default, `0` will limit output to periods (`.`) for successful commands, and exclamation marks for errors. |

All `RGB` values can be `RGB` or `RRGGBB`.  Commands end with a semicolon.

# Ports

## ItsyBitsy M4

| Port | Default Pin |
|:-:|:-:|
| `0` | `14/A0` |
| `1` | `15/A1` |
| `2` | `16/A2` |
| `3` | `17/A3` |
| `4` | `18/A4` |
| `5` | `19/A5` |
