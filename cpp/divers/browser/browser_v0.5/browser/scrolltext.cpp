/*
Browser
Copyright (C) 2012  Sebastien Celles

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "scrolltext.h"
#include <QPainter>
#include <QDebug>

//ScrollText::ScrollText(QWidget *parent) : QWidget(parent), scrollPos(0)
ScrollText::ScrollText(QWidget *parent) : QLabel(parent), scrollPos(0)
{
    staticText.setTextFormat(Qt::PlainText);
    //staticText.setTextFormat(Qt::RichText);

    setFixedHeight(fontMetrics().height());
    leftMargin = height() / 3;

    setSeparator("   ===   "); // === ---

    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    timer.setInterval(50);

    //setAlignment(Qt::AlignHCenter);
}

QString ScrollText::text() const
{
    return _text;
}

void ScrollText::setText(QString text)
{
    if (text!=_text) {
        _text = text;
        updateText();
        update();
    }
}

QString ScrollText::separator() const
{
    return _separator;
}

void ScrollText::setSeparator(QString separator)
{
    _separator = separator;
    updateText();
    update();
}

void ScrollText::updateText()
{
    timer.stop();

    singleTextWidth = fontMetrics().width(_text);

    //scrollEnabled = (singleTextWidth > width() - leftMargin);

    scrollEnabled = _text.length()>0;

    if(scrollEnabled)
    {
        scrollPos = -64;
        staticText.setText(_text + _separator);
        timer.start();
    } else {
//        staticText.setText(_text);
        staticText.setText("Pas de message");
    }

    staticText.prepare(QTransform(), font());
    wholeTextSize = QSize(fontMetrics().width(staticText.text()), fontMetrics().height());
}

void ScrollText::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    if(scrollEnabled)
    {
        buffer.fill(qRgba(0, 0, 0, 0));
        QPainter pb(&buffer);
        pb.setPen(p.pen());
        pb.setFont(p.font());

        int x = qMin(-scrollPos, 0) + leftMargin;
        while(x < width())
        {
            pb.drawStaticText(QPointF(x, (height() - wholeTextSize.height()) / 2) + QPoint(2, 2), staticText);
            x += wholeTextSize.width();
        }

        //Apply Alpha Channel
        pb.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        pb.setClipRect(width() - 15, 0, 15, height());
        pb.drawImage(0, 0, alphaChannel);
        pb.setClipRect(0, 0, 15, height());
        //initial situation: don't apply alpha channel in the left half of the image at all; apply it more and more until scrollPos gets positive
        if(scrollPos < 0)
            pb.setOpacity((qreal)(qMax(-8, scrollPos) + 8) / 8.0);
        pb.drawImage(0, 0, alphaChannel);

        //pb.end();
        p.drawImage(0, 0, buffer);
    }
    else
    {
        p.drawStaticText(QPointF(leftMargin, (height() - wholeTextSize.height()) / 2), staticText);
    }
}

void ScrollText::resizeEvent(QResizeEvent*)
{
    //When the widget is resized, we need to update the alpha channel.

    alphaChannel = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);

    //Create Alpha Channel:
    if(width() > 64)
    {
        //create first scanline
        QRgb* scanline1 = (QRgb*)alphaChannel.scanLine(0);
        for(int x = 1; x < 16; ++x)
            scanline1[x - 1] = scanline1[width() - x] = qRgba(0, 0, 0, x << 4);
        for(int x = 15; x < width() - 15; ++x)
            scanline1[x] = qRgb(0, 0, 0);
        //copy scanline to the other ones
        for(int y = 1; y < height(); ++y)
            memcpy(alphaChannel.scanLine(y), (uchar*)scanline1, width() * 4);
    }
    else
        alphaChannel.fill(qRgb(0, 0, 0));


    //Update scrolling state
    bool newScrollEnabled = (singleTextWidth > width() - leftMargin);
    if(newScrollEnabled != scrollEnabled)
        updateText();
}

void ScrollText::timer_timeout()
{
    scrollPos = (scrollPos + 2)
                % wholeTextSize.width();
    update();
}