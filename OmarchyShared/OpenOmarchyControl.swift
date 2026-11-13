import AppIntents

@available(iOS 18.0, *)
enum OmarchyDestination: String, AppEnum {
    case desktop
    static var typeDisplayRepresentation: TypeDisplayRepresentation = "Omarchy"
    static var caseDisplayRepresentations: [OmarchyDestination: DisplayRepresentation] = [
        .desktop: DisplayRepresentation(title: "Desktop", image: .init(systemName: "desktopcomputer"))
    ]
}

@available(iOS 18.0, *)
struct OpenOmarchyControl: OpenIntent {
    static var title: LocalizedStringResource = "Open Omarchy"
    static var openAppWhenRun: Bool { true }
    @Parameter(title: "Destination") var target: OmarchyDestination
    init() { target = .desktop }
    @MainActor func perform() async throws -> some IntentResult {
#if !OMARCHY_WIDGET_EXTENSION
        try DeeplinkCoordinator.openOmarchyShortcut()
#endif
        return .result()
    }
}
