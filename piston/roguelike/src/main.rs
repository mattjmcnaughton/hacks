extern crate glutin_window;
extern crate graphics;
extern crate opengl_graphics;
extern crate piston;

use glutin_window::GlutinWindow;
use opengl_graphics::{GlGraphics, OpenGL};
use piston::event_loop::{EventSettings, Events};
use piston::{RenderEvent, WindowSettings};

const RED: [f32; 4] = [1.0, 0.0, 0.0, 1.0];
const GREEN: [f32; 4] = [0.0, 1.0, 0.0, 1.0];
const BLUE: [f32; 4] = [0.0, 0.0, 1.0, 1.0];
const WHITE: [f32; 4] = [1.0;4];

const GAME_TITLE: &str = "roguelike";

fn main() {
    let settings = WindowSettings::new(GAME_TITLE, [512; 2]).exit_on_esc(true);
    let mut window: GlutinWindow = settings.build().expect("Could not create window");
    let mut gl = GlGraphics::new(OpenGL::V3_2);


    let mut events = Events::new(EventSettings::new());

    // `while let Some` is equivalent to "while we have events" (i.e. the `Option` is `Some` and
    // not `None`)
    while let Some(e) = events.next(&mut window) {
        // `if let Some` is a more elegant way of saying `if `Options` returned by `render_args` is
        // `Some` and not `None` (and condition is truthy).
        if let Some(r) = e.render_args() {
            gl.draw(r.viewport(), |_c, g| {
                graphics::clear(BLUE, g);
            });
        }
    }
}
