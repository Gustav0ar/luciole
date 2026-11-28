# Scope

Luciole is a native Wayland file manager built to stay smooth: quick to start, fluid in large folders, and never blocked by previews. It is built by the people who use it daily. It is young and under heavy development, and the fastest way to make it worse is to grow it in every direction at once. This file records what the project takes on and what it declines, so a request gets a predictable answer instead of a case-by-case one.

Read the project [ethos](https://noctalia.dev/ethos) for the values behind these lines, and [CONTRIBUTING.md](CONTRIBUTING.md) for the technical principles they follow from.

> [!NOTE]
> **Localization is not open for contributions yet.** It was deliberately kept for late in development: user-facing strings change constantly, and translating them early would mean redoing the work over and over. The maintainers are building the translation system themselves, and translation contributions will open once it lands. That will be announced here.

## In scope

- Bugs, crashes, regressions, and slowness in anything Luciole already does.
- Refinement of the surfaces that already exist: grid, list, and Miller column views, tabs, split view, and windows, search and filtering, file operations and Undo and Redo, archives, the places sidebar, the portal file picker, remote locations (SFTP, SMB, WebDAV), Open With, and custom scripts.
- Settings that expose behavior Luciole already implements.
- freedesktop standards that real setups depend on: the thumbnail cache, Trash, MIME types, bookmarks, and the FileChooser portal.
- Performance: startup time, scrolling, memory use, and keeping the window responsive.
- Documentation, packaging, and test coverage for all of the above.

## Out of scope

- **An image viewer.** Thumbnails and previews are in scope; slideshows, editing, and viewer-style navigation are not. Open With hands the file to a real viewer.
- **A terminal pane.** The open terminal action and custom scripts already cover this.
- **Changes to `lib/`.** It is a copy of noctalia-shell code. Fixes and features for it go upstream to noctalia-shell.
- **Other toolkits or backends:** Qt, GTK, X11, or software rendering.
- **A plugin system, embedded scripting language, or runtime module loading.** Custom scripts are the extension point.
- **Built-in editors and players:** text editing, audio or video playback, or a PDF reader. Previewing is in scope; editing and playback are not.
- **Desktop shell duties:** desktop icons, a desktop mode, wallpaper handling, launchers, or application menus. Those belong to a shell, for example [Noctalia](https://github.com/noctalia-dev/noctalia).
- **A commander-style dual-pane interface.** Refining split view is in scope; a second interface paradigm is not.
- **Content indexing and full-text search**, such as Tracker or Baloo integration. Filename search and filtering stay.
- **File tagging and extended attribute metadata editing.**
- **Built-in cloud or sync clients.** Locations reachable through mounts or GVfs are already supported.
- **Feature parity with another file manager as the motivation.** "Project X has this" describes Project X, not a problem you have.
- **Configuration formats other than TOML**, and compatibility aliases, migration readers, or silent fallbacks for renamed settings.
- **Per-application or per-distribution special cases.**

"Out of scope" is not a verdict on the idea. It means the work does not belong in this project, at this stage, with this maintenance budget.

## How a request is judged

1. **Does it need the file manager?** If a script, Open With, or another application can do it, that is where it belongs.
2. **Does it extend something that exists, or open a new front?** Sharpening current behavior beats adding surface.
3. **Does it keep the window responsive?** Anything that blocks the UI thread is declined, whatever it adds.
4. **Who maintains it in a year?** Every option, setting, and code path is carried forward.

A request that survives all four is worth an issue. One that does not is still worth a conversation, just not a tracking issue.

## Where to raise things

- **Bug or regression:** open a bug report. These are always welcome, including small ones.
- **Idea, question, or "would you consider":** ask on [Discord](https://discord.noctalia.dev) first. It is faster than an issue and it survives being wrong.
- **Large or invasive pull request:** agree on the change before writing it. An unsolicited rewrite can be declined on scope alone, and nobody enjoys that outcome.

This file is not a promise that the answer stays no forever. Scope widens deliberately, when the foundation is stable enough to carry the addition, and it is recorded here when it does.
