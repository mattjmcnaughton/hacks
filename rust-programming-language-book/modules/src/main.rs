// Look in `sound.rs` for contents of the sound module.
mod sound;

fn main() {
    // main can refer to `sound` because it is defined in the same module. It can refer to
    // `instrument` and `clarinet` because they are both public.
    sound::instrument::clarinet();
}
