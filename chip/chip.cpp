// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "chip.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


Chip::Chip(const QColor &color, int x, int y, int radius, int nodeid)
{
    this->x = x-radius;
    this->y = y-radius;
    this->color = color;
    this->radius = radius;
    this->nodeid = nodeid;

//    qDebug() << this->nodeid ;

    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

}

QRectF Chip::boundingRect() const
{
    return QRectF(0, 0, this->radius, this->radius);
}

QPainterPath Chip::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, this->radius, this->radius);
    return path;
}

void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.darker(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.lighter(125);

//    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
//    if (lod < 0.2) {
//        if (lod < 0.125) {
//            painter->fillRect(QRectF(0, 0, this->radius, this->radius), fillColor);
//            return;
//        }

//        QBrush b = painter->brush();
//        painter->setBrush(fillColor);
//        painter->drawRect(0, 0, this->radius, this->radius);
//        painter->setBrush(b);
//        return;
//    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 1;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(0, 0, this->radius, this->radius)); // chip main
    painter->setBrush(b);

    //    qDebug() << this->nodeid;

//    if (lod >= 1) {
//        qDebug() << "here" ;
//        painter->setPen(QPen(Qt::gray, 1));
//        painter->drawLine(15, 54, 94, 54);
//        painter->drawLine(94, 53, 94, 15);
//        painter->setPen(QPen(Qt::black, 0));
//    }

    // Draw text
//    if (lod >= 2) {
//        QFont font("Times", 10);
//        font.setStyleStrategy(QFont::ForceOutline);
//        painter->setFont(font);
//        painter->save();
//        painter->scale(0.1, 0.1);
//        painter->drawText(170, 180, QString("Model: VSC-2000 (Very Small Chip) at %1x%2").arg(x).arg(y));
//        painter->drawText(170, 200, QString("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
//        painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
//        painter->restore();
//    }

    // Draw lines
//    QVarLengthArray<QLineF, 36> lines;
//    if (lod >= 0.5) {
//        for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
//            lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
//            lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
//        }
//        for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
//            lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
//            lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
//        }
//    }
//    if (lod >= 0.4) {
//        const QLineF lineData[] = {
//            QLineF(25, 35, 35, 35),
//            QLineF(35, 30, 35, 40),
//            QLineF(35, 30, 45, 35),
//            QLineF(35, 40, 45, 35),
//            QLineF(45, 30, 45, 40),
//            QLineF(45, 35, 55, 35)
//        };
//        lines.append(lineData, 6);
//    }
//    painter->drawLines(lines.data(), lines.size());

    // Draw red ink
//    if (stuff.size() > 1) {
//        QPen p = painter->pen();
//        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//        painter->setBrush(Qt::NoBrush);
//        QPainterPath path;
//        path.moveTo(stuff.first());
//        for (int i = 1; i < stuff.size(); ++i)
//            path.lineTo(stuff.at(i));
//        painter->drawPath(path);
//        painter->setPen(p);
//    }
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Chip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}


void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    qDebug() << this->nodeid;
    update();
}
