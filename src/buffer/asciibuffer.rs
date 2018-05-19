use dim::Dim;

pub struct Asciibuffer<'a> {
    pub dim: Dim,

    pub background: u32,
    pub color_type: u32,
    pub pixel_size: u8,

    pub buffer: &'a str
}
