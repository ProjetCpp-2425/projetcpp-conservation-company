#include "statwidget.h"
#include <QPainter>
#include <cmath>

StatWidget::StatWidget(QWidget *parent) : QWidget(parent) {}

//Dès que de nouvelles données sont reçues via setStatistics, le graphique s'adapte automatiquement grâce à l'appel de update.
void StatWidget::setStatistics(const QMap<QString, int> &stats) {

    //QMap<QString, int> statistics; // Contient les données pour le graphique
    statistics = stats;// // Stocke les statistiques dans le membre 'statistics'
    update();
}



void StatWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (statistics.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Base de la couleur et ses dégradations
    QColor baseColor = QColor(70, 130, 180); // Bleu acier
    QVector<QColor> colors;
    for (int i = 0; i < statistics.size(); ++i) {
        colors.append(baseColor.lighter(100 + i * 20)); // Génère des couleurs plus claires
    }

    // Calcul du total des points
    int total = 0;
    for (int value : statistics.values()) {
        total += value;
    }

    // Adapter le cercle pour qu'il utilise tout l'espace disponible dans le widget
    int margin = 50; // Augmenter la marge pour réduire la taille du cercle
    QRectF circleBounds(margin, margin, width() - 2 * margin, height() - 2 * margin);

    // Angle de départ
    int startAngle = 0;

    int colorIndex = 0;

    // Dessiner chaque segment
    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        int spanAngle = std::round(360.0 * it.value() / total * 16); // Proportion de l'angle

        // Dessiner le segment
        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawPie(circleBounds, startAngle, spanAngle);

        startAngle += spanAngle;
        colorIndex++;
    }

    // Légende : dessiner sous le diagramme
    int legendY = height() - 120; // Placer la légende un peu plus bas
    int legendX = margin;

    colorIndex = 0;
    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawRect(legendX, legendY, 20, 20); // Carré de couleur
        painter.drawText(legendX + 30, legendY + 15, it.key() + " (" + QString::number(it.value()) + ")");
        legendY += 25; // Déplacer la légende sur la ligne suivante

        // Si la légende déborde, passer à la colonne suivante
        if (legendY > height() - margin) {
            legendY = height() - 120;
            legendX += 150; // Décalage pour la colonne suivante
        }

        colorIndex++;
    }
}


