mod buffer;
mod dim;
mod renderer;

use buffer::asciibuffer::Asciibuffer;
use buffer::imagebuffer::Imagebuffer;
use buffer::buffer2d::Buffer2d;
use renderer::fill::render_fill;
use dim::Dim;

fn main () {
    let asciibuffer =
        render_fill(
            Imagebuffer {
                background: 0,
                color_type: 0,
                pixel_size: 0,
                buffer: Buffer2d {
                    dim: Dim { height: 0, width: 0 },
                    buffer: Vec::new()
                }
            },
            Dim { height: 0, width: 0 },
        );
}
