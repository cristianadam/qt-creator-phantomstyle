#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/manhattanstyle.h>

#include <extensionsystem/iplugin.h>

#include <QApplication>

#include <phantom/phantomstyle.h>

namespace Phantom::Internal {

class PhantomStylePlugin final : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "PhantomStylePlugin.json")

public:
    PhantomStylePlugin() = default;

    ~PhantomStylePlugin() final {}

    void initialize() final
    {
        const auto *proxyStyle = qobject_cast<QProxyStyle *>(QApplication::style());
        const bool havePhantom = proxyStyle && proxyStyle->baseStyle()->objectName() == "Phantom";
        if (!havePhantom && !qEnvironmentVariableIsSet("QTCREATOR_USE_DEFAULT_STYLE")) {
            auto manhattanStyle = new ManhattanStyle(QApplication::style()->name());
            manhattanStyle->setBaseStyle(new PhantomStyle);

            QApplication::setStyle(manhattanStyle);
        }
    }

    void extensionsInitialized() final {}

    ShutdownFlag aboutToShutdown() final { return SynchronousShutdown; }
};

} // namespace Phantom::Internal

#include <phantomstyleplugin.moc>
