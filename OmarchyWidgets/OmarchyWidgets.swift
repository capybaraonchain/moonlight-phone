import SwiftUI
import WidgetKit

struct OmarchyEntry: TimelineEntry { let date: Date }
struct OmarchyProvider: TimelineProvider {
    func placeholder(in context: Context) -> OmarchyEntry { OmarchyEntry(date: .now) }
    func getSnapshot(in context: Context, completion: @escaping (OmarchyEntry) -> Void) { completion(placeholder(in: context)) }
    func getTimeline(in context: Context, completion: @escaping (Timeline<OmarchyEntry>) -> Void) {
        completion(Timeline(entries: [placeholder(in: context)], policy: .never))
    }
}
struct OmarchyLaunchView: View {
    @Environment(\.widgetFamily) private var family
    var body: some View {
        Group {
            switch family {
            case .accessoryCircular:
                Image(systemName: "desktopcomputer").font(.title2)
            case .accessoryInline:
                Label("Omarchy", systemImage: "desktopcomputer")
            case .accessoryRectangular:
                Label { VStack(alignment: .leading) { Text("Omarchy").bold(); Text("Open stream").font(.caption) } }
                    icon: { Image(systemName: "desktopcomputer").font(.title2) }
            default:
                VStack(spacing: 12) { Image(systemName: "desktopcomputer").font(.largeTitle); Text("Omarchy").bold(); Text("Open stream").font(.caption) }
            }
        }
        .widgetURL(URL(string: "moonlightphone://omarchy")!)
        .containerBackground(.fill.tertiary, for: .widget)
        .accessibilityLabel("Open Omarchy stream")
    }
}
struct OmarchyLaunchWidget: Widget {
    var body: some WidgetConfiguration {
        StaticConfiguration(kind: "com.capy.moonlightphone.launch", provider: OmarchyProvider()) { _ in OmarchyLaunchView() }
            .configurationDisplayName("Omarchy")
            .description("Open your desktop stream with one tap.")
            .supportedFamilies([.accessoryCircular, .accessoryRectangular, .accessoryInline, .systemSmall])
    }
}
struct OmarchyStreamControl: ControlWidget {
    var body: some ControlWidgetConfiguration {
        StaticControlConfiguration(kind: "com.capy.moonlightphone.control") {
            ControlWidgetButton(action: OpenOmarchyControl()) { Label("Omarchy", systemImage: "desktopcomputer") }
        }
        .displayName("Omarchy")
        .description("Open your Omarchy desktop stream.")
    }
}
@main struct OmarchyWidgetsBundle: WidgetBundle {
    var body: some Widget { OmarchyLaunchWidget(); OmarchyStreamControl() }
}
