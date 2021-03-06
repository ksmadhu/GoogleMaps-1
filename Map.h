#include <exception>
using namespace std;

#ifndef __Map_h__
#define __Map_h__

//#include "MapTypeRegistry.h"
#include <QMap>
#include <QVariant>
#include "MapOptions.h"
#include "LatLngBounds.h"
#include "LatLng.h"
#include "Size.h"
#include "Marker.h"
#include "MarkerOptions.h"
#include "Polygon.h"
#include "PolygonOptions.h"

namespace googleMaps
{
	class MapTypeRegistry;
	class MapOptions;
	class LatLngBounds;
	class LatLng;
	class MouseEvent;
    class Marker;
    class MarkerOptions;
	// class AbstractGoogleMapsService;
	class Map;
    class Size;
    class Polygon;
    class PolygonOptions;
}

namespace googleMaps
{
    


    class MapType: public QObject
    {
        Q_OBJECT
        protected:
            int m_maxZoom;
            int m_minZoom;
            int m_radius;
            QString m_alt;
            QString m_name;
            QString m_projection;
            googleMaps::Size m_tileSize;

        public:
            explicit MapType(QObject* parent = 0){m_radius = 6378137; setParent(parent);}
            void googleMaps::MapType::setAlt(QString alt) { this->m_alt = alt;  }
            QString googleMaps::MapType::getAlt() { return this->m_alt; }
            void googleMaps::MapType::setMaxZoom(int maxZoom) {this->m_maxZoom = maxZoom;}
            int googleMaps::MapType::getMaxZoom() {return this->m_maxZoom;}
            void googleMaps::MapType::setMinZoom(int minZoom) { this->m_minZoom = minZoom; }
            int googleMaps::MapType::getMinZoom() { return this->m_minZoom; }
            void googleMaps::MapType::setName(QString name) { this->m_name = name; }
            QString googleMaps::MapType::getName() { return this->m_name; }
            void googleMaps::MapType::setTileSize(googleMaps::Size tileSize) { this->m_tileSize = tileSize; }
            googleMaps::Size googleMaps::MapType::getTileSize() { return this->m_tileSize; }
    };


    class MapTypeRegistry: public QObject
    {
        Q_OBJECT
        protected:
            QMap<QString, googleMaps::MapType*> registry;
        public:
            explicit MapTypeRegistry(QObject* parent = 0) {setParent(parent);}
            void set(QString id, MapType* mapType) {registry[id] = mapType;}
            QMap<QString, googleMaps::MapType*> get() const {return registry;}
            MapTypeRegistry(const googleMaps::MapTypeRegistry& rhs)
            {
                for (auto key : rhs.get().keys())
                {
                    MapType*  type = rhs.get().value(key);
                    registry.insert(key, type);
                }
            }
            googleMaps::MapTypeRegistry& googleMaps::MapTypeRegistry::operator =(const googleMaps::MapTypeRegistry& rhs)
            {
                if(this == &rhs)
                {
                    return *this;
                }
                for (auto key : rhs.get().keys())
                {
                    MapType*  type = rhs.get().value(key);
                    registry.insert(key, type);
                }
                return *this;
            }

    };

    
    class Map: public QObject
	{
        Q_OBJECT
        Q_PROPERTY(googleMaps::LatLngBounds bounds READ getBounds NOTIFY boundsChanged WRITE updateBounds)
        Q_PROPERTY(googleMaps::LatLng center READ getCenter NOTIFY centerChanged WRITE centerMapAt)
        Q_PROPERTY(int zoom READ getZoom WRITE updateZoom NOTIFY zoom_changed)
        Q_PROPERTY(QString mapsKey READ getMapsKey NOTIFY mapsKeySet)
        Q_PROPERTY(QVariantMap options READ getOptionsMap NOTIFY optionsChanged)
        Q_PROPERTY(bool mapLoaded READ getMapLoaded WRITE updateMapLoaded NOTIFY mapLoadedChanged)

        protected:
            googleMaps::MapTypeRegistry m_mapTypes;
            googleMaps::LatLngBounds m_bounds;
            googleMaps::MapOptions m_options;
            googleMaps::LatLng m_mapCenter;
            QString m_mapTypeID;
            int m_tilt;
            int m_zoom;
            bool m_mapLoaded;
            QString m_mapsKey;
            QList<googleMaps::Marker> m_markers;
            QList<googleMaps::Polygon> m_polygons;

        public:
            explicit Map( QObject* parent = 0);
            Map(const MapOptions options);
            Map(const googleMaps::Map &rhs);
            //assignment operator
            googleMaps::Map& operator=(const googleMaps::Map &rhs);
            virtual ~Map();
            void fitBounds(googleMaps::LatLngBounds bounds);
            googleMaps::LatLngBounds getBounds() const;
            googleMaps::LatLng getCenter() const;
            googleMaps::MapOptions getOptions() const;
            QString getMapTypeId() const;
            googleMaps::MapTypeRegistry getMapTypes() const;
            int getZoom() const;
            int getTilt() const;
            void panMapTo(googleMaps::LatLng latLng);
            void setMapsKey(const QString key);
            //void setOptions(const googleMaps::MapOptions options);
            Q_INVOKABLE QString getMapsKey() const;
            void sendZoomOutRequest();
            void sendZoomInRequest();
            Q_INVOKABLE QVariantMap getOptionsMap() const;
            Q_INVOKABLE bool getMapLoaded() const;
            static googleMaps::Marker createMarker(const MarkerOptions options);

            
        public slots:
            void updateMapTypeId(const QString mapTypeId);
            void updateZoom(const   QVariant zoom);
            void updateCenter(const QVariant latlng);
            void updateOptions(const googleMaps::MapOptions options);
            void updateTilt(const int tilt);
            void updateBounds(const LatLngBounds latLngBounds);
            void centerMapAt(const googleMaps::LatLng latLng);
            void panToBound(const googleMaps::LatLngBounds latLngBounds);
            void updateMapTypes(const googleMaps::MapTypeRegistry mapTypes);
            void startMap();
            void addMarker(googleMaps::MarkerOptions options);
            void clearMarker(googleMaps::LatLng position);
            void clearMarkers();
            void addPolygon(googleMaps::PolygonOptions options);
            void clearPolygon(googleMaps::PolygonOptions options);
            void clearPolygons();
            void updateMapLoaded(const bool loaded);

        signals:
            void boundsChanged(googleMaps::LatLngBounds latLngBounds);
            void centerChanged(googleMaps::LatLng position);
            void click(googleMaps::LatLng mapLocation);
            void dblclick(googleMaps::LatLng mapLocation);
            void drag();
            void dragend();
            void dragstart();
            void maptypeid_changed();
            void resize();
            void zoom_changed(qreal zoomLevel);
            void centerOnLocation(qreal lat, qreal lng);
            void mapsKeySet();
            void optionsChanged();
            void startMapView();
            void addMarkerRequest(QVariantMap options);
            void clearMarkerRequest(QVariantMap position);
            void clearAllMarkersRequest();
            void addPolygonRequest(QVariantMap options);
            void clearPolygonRequest(googleMaps::PolygonOptions options);
            void clearPolygonsRequest();
            void zoomInRequest();
            void zoomOutRequest();
            void updateMapOptionsRequest(QVariantMap options);
            void updateMapTypeRequest(QString type);
            void mapLoadedChanged();

	};
}

Q_DECLARE_METATYPE(googleMaps::Map)

#endif
