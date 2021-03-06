// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#include "ZoneSet.h"

#include <QDomNode>

ZoneSet::ZoneSet(const QDomElement& el, const PropertyFactory& propFactory) {
  const QString zoneStr("zone");

  QDomNode node(el.firstChild());
  for (; !node.isNull(); node = node.nextSibling()) {
    if (!node.isElement()) {
      continue;
    }
    if (node.nodeName() != zoneStr) {
      continue;
    }

    const Zone zone(node.toElement(), propFactory);
    if (zone.isValid()) {
      m_zones.push_back(zone);
    }
  }
}

QDomElement ZoneSet::toXml(QDomDocument& doc, const QString& name) const {
  const QString zoneStr("zone");

  QDomElement el(doc.createElement(name));
  for (const Zone& zone : m_zones) {
    el.appendChild(zone.toXml(doc, zoneStr));
  }
  return el;
}
