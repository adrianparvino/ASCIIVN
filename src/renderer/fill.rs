use buffer::imagebuffer::Imagebuffer;
use buffer::asciibuffer::Asciibuffer;
use dim::Dim;

pub fn render_fill<'a>(dst: Imagebuffer,
                       dim: Dim) -> Option<Asciibuffer<'a>>
{
    if (dst.buffer.dim.width  % dim.width  != 0) { return None; }
    if (dst.buffer.dim.height % dim.height != 0) { return None; }

    Some(Asciibuffer {
        dim,
        background: 0,
        color_type: 0,
        pixel_size: 0,
        buffer: ""
    })
}