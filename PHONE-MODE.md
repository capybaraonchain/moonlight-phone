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
- A collapsible safe-area toolbar provides Apps, Launch, Type, Drag, Resize, More
  and Hide. Apps switches running windows; Launch opens the application grid.
  Keyboard shortcuts are available under More.
- Hide fully removes the toolbar in both orientations. Start a one-finger swipe
  in the narrow bottom edge and move upward at least 64 points, then lift and tap
  **Show controls**. The confirmation expires after four seconds. Short, diagonal,
  cancelled and multi-finger gestures cannot open the toolbar; the edge contact
  is consumed locally without touching the remote desktop. Rotation/backgrounding
  cancels a pending confirmation. VoiceOver offers the same confirmation action.
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

### Direct window controls (November 12 update)

Tap an app, then tap the dedicated **Resize** button (or **More → Move window**).
Slide one finger anywhere in the stream; lift and continue as needed. The Resize
button becomes **Done** while either window tool is active; tap it to return to
native touch. These controls do not simulate a mouse or hold modifier keys.
Dragging files is still the separate **Drag / Pick / Drop** control.

The companion `host/omarchy-phone-window` uses port 47992 with mandatory mutual
TLS. It reuses Sunshine's server certificate and trusts only enabled paired
client certificates, including revocation on existing connections. It exposes
only begin/update/end window geometry operations while the phone display lease
is active. Gesture tokens are bound to the paired client, exact window/PID and
phone-session resolution/nonce. The existing display-handoff lock excludes
rotation conflicts; special Agent Desktop windows are excluded. It never changes
outputs, restarts apps or invokes a shell with client input.

The host keeps a reachable title-bar grip while allowing freely positioned windows,
including sizes larger than the screen and partially offscreen positions.
Applications that insist on a minimum size remain anchored; the phone explains
the limit instead of silently sending ineffective mouse input. Use Roomy layout
for applications that need more desktop space.

### Open Omarchy from Home Screen or Control Center

The **Open Omarchy** App Shortcut has no parameters. It connects directly to the
paired PC named `omarchy`, or to the sole paired desktop when there is only one.
An existing stream is brought forward without restarting it. Open the PC once
in Moonlight Phone after pairing so its Desktop entry is cached. Desktop targets
also appear automatically in the generic Open VoidLink Target action.

In Shortcuts, create a shortcut named **Omarchy** containing **Open Omarchy**
from Moonlight Phone. Add it to Home Screen, select it in a Shortcuts widget,
or add a Shortcut control in Control Center and choose Omarchy. This uses
Apple's built-in widgets and controls and needs no additional signed extension.

### Native widgets, controls and text input

Keep app extensions when AltStore asks. **Omarchy** is now offered as a Lock
Screen circular/rectangular/inline widget and a small Home Screen widget. Its
control is available in Control Center and the Lock Screen's bottom controls.
Both open the paired desktop through the existing Open Omarchy flow. iOS may
require Face ID/unlock before opening the app.

A brief tap inside an accessible editable field opens the keyboard automatically.
Enter sends Return to the desktop and dismisses the keyboard. Focus checks run
locally on the host over the existing paired TLS connection and expose only a
boolean; text and field values are never read. Unsupported accessibility falls
back to Type. Electron/Chrome need accessibility enabled; configured launchers
use --force-renderer-accessibility on their next launch.
