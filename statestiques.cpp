#include "statestiques.h"
#include <QPainter>
#include <QDebug>

StatWidget::StatWidget(QWidget *parent) : QWidget(parent) {}

void StatWidget::setStatistics(const QMap<QString, int> &stats) {
    statistics = stats;
    update();
}

void StatWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (statistics.isEmpty()) {
        QPainter painter(this);
        painter.drawText(rect(), Qt::AlignCenter, "Aucune donnée disponible");
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define colors for the pie chart
    QVector<QColor> colors = {
        QColor(255, 99, 132),   // Red
        QColor(54, 162, 235),   // Blue
        QColor(255, 206, 86),   // Yellow
        QColor(75, 192, 192),   // Teal
        QColor(153, 102, 255)   // Purple
    };

    // Calculate total
    int total = 0;
    for (int value : statistics.values()) {
        total += value;
    }

    // Calculate dimensions for the pie chart
    int margin = 60;
    int pieSize = qMin(width(), height() - 100) - 2 * margin;
    QRectF pieRect((width() - pieSize) / 2, margin, pieSize, pieSize);

    // Draw the pie chart
    int startAngle = 0;
    int colorIndex = 0;

    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        if (it.value() > 0) {  // Only draw if there's a value
            // Calculate angle for this slice (multiply by 16 as Qt uses 1/16th of a degree)
            int spanAngle = (it.value() * 5760) / total;  // 5760 = 16 * 360

            painter.setPen(Qt::white);  // White border between slices
            painter.setBrush(colors[colorIndex % colors.size()]);
            painter.drawPie(pieRect, startAngle, spanAngle);

            startAngle += spanAngle;
        }
        colorIndex++;
    }

    // Draw legend
    int legendX = width() - 150;  // Right side of the widget
    int legendY = margin;
    colorIndex = 0;

    painter.setFont(QFont("Arial", 10));

    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        if (it.value() > 0) {  // Only show in legend if there's a value
            // Draw color box
            painter.setBrush(colors[colorIndex % colors.size()]);
            painter.setPen(Qt::black);
            painter.drawRect(legendX, legendY, 15, 15);

            // Draw text
            QString percentage = QString::number((double)it.value() / total * 100, 'f', 1);
            QString legendText = QString("%1: %2 (%3%)")
                               .arg(it.key())
                               .arg(it.value())
                               .arg(percentage);

            painter.drawText(legendX + 20, legendY + 12, legendText);

            legendY += 25;  // Move down for next legend item
        }
        colorIndex++;
    }
}
