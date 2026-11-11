# Moonlight Phone

A personal iPhone desktop build from VoidLink's current `Integration` branch,
based on upstream commit `4001382fcd04e1cf998e84b9603397315473bf14`
(2026-11-11). This is an unsigned source build for AltStore, not the old
Moonlight-ZWM 9.0.2 release and not an App Store distribution.

## Phone behavior

- Orientation unlocked on first launch, with current upstream's SwiftUI settings
  interface available in portrait and landscape.
- Full-screen resolution chosen automatically at 60 FPS. Video dimensions are
  aligned before persistence and negotiation to avoid Sunshine CUDA's odd-width
  chroma-copy failure. iPhone 15 Pro uses 1176 × 2556, three pixels narrower than
  its native 1179 × 2556 panel, at a 3× host desktop scale.
- Absolute touch enabled by default, without an on-screen gamepad overlay.
- A collapsible safe-area toolbar provides Apps, Keys, Type, Drag, and Settings.
- Drag arms a persistent left-button hold: touch the source, move it, lift and
  reposition fingers as needed, then tap Drop. Cancellation, backgrounding and
  leaving the stream release the mouse button.
- Keyboard shortcuts include app switching, launcher, Copy, Paste, Cut, Undo,
  Redo, Select All, Escape, Tab, Previous Field and Enter. They use PC key codes
  appropriate for a Linux Sunshine host.

## Build and install

The `Build Moonlight Phone` workflow builds the `phone` branch on a standard
GitHub-hosted Xcode runner. It uploads an unsigned IPA and the build log. No
Apple signing credentials or machine-specific host configuration belong in
this repository. Sign/install the resulting IPA with AltStore.

The original GPL license and upstream authorship remain intact. Current
VoidLink source and acknowledgments: https://github.com/The-Fried-Fish/VoidLink-previously-moonlight-zwm
