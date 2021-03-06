#include "googlemaps_plugin.h"
#include <QQmlExtensionPlugin>
#include <qqml.h>

void GoogleMapsPlugin::registerTypes(const char *uri)
{
    // @uri google.maps
    Q_ASSERT(uri == QLatin1String("GoogleMaps"));
    qmlRegisterType<googleMaps::GeocoderComponentRestrictions>(uri, 1, 0, "GeocoderComponentRestrictions");
    qmlRegisterType<googleMaps::GeocoderAddressComponent>(uri, 1, 0, "GeocoderAddressComponent");
    qmlRegisterType<googleMaps::GeocoderGeometry>(uri, 1, 0, "GeocoderGeometry");
    qmlRegisterType<googleMaps::GeocoderRequest>(uri, 1, 0, "GeocoderRequest");
    qmlRegisterType<googleMaps::GeocoderResult>(uri, 1, 0, "GeocoderResult");
    qmlRegisterType<googleMaps::LatLng>(uri, 1, 0, "LatLng");
    qmlRegisterType<googleMaps::LatLngBounds>(uri, 1, 0, "LatLngBounds");
    qmlRegisterType<googleMaps::SphericalGeometry>(uri, 1, 0, "SphericalGeometry");
    qmlRegisterType<googleMaps::MaxZoomService>(uri, 1, 0, "MaxZoomService");
    qmlRegisterType<googleMaps::Geocoder>(uri, 1, 0, "Geocoder");
    qmlRegisterType<googleMaps::ElevationService>(uri, 1, 0, "ElevationService");
    qmlRegisterType<googleMaps::GoogleMaps>(uri, 1, 0, "GoogleMaps");
    qmlRegisterType<googleMaps::Map>(uri, 1, 0, "Map");
    qmlRegisterType<googleMaps::MapOptions>(uri, 1, 0, "MapOptions");
    qmlRegisterType<googleMaps::Marker>(uri, 1, 0, "Marker");
    qmlRegisterType<googleMaps::MarkerOptions>(uri, 1, 0, "MarkerOptions");
    qmlRegisterType<googleMaps::Size>(uri, 1, 0, "Size");
    qmlRegisterType<googleMaps::Point>(uri, 1, 0, "Point");
    qmlRegisterType<googleMaps::Polygon>(uri, 1, 0, "Polygon");
    qmlRegisterType<googleMaps::PolygonOptions>(uri, 1, 0, "PolygonOptions");
}

void GoogleMapsPlugin::computeArea(const QList<googleMaps::LatLng>& path)
{

}

void GoogleMapsPlugin::computeDistanceBetween(const googleMaps::LatLng& from, const googleMaps::LatLng& to)
{

}

void GoogleMapsPlugin::computeHeading(const googleMaps::LatLng& from, const googleMaps::LatLng& to)
{

}

void GoogleMapsPlugin::computeLength(const QList<googleMaps::LatLng>& path)
{

}

void GoogleMapsPlugin::computeOffset(const googleMaps::LatLng& from, const qreal& distance, const qreal& heading)
{

}

void GoogleMapsPlugin::computeOffsetOrigin(const googleMaps::LatLng& to, const qreal& distance, const qreal& heading)
{

}

void GoogleMapsPlugin::interpolate(googleMaps::LatLng& from, googleMaps::LatLng& to, qreal& fraction)
{

}

void GoogleMapsPlugin::centerMapAt(googleMaps::LatLng newCenter)
{

}

void GoogleMapsPlugin::getMaxZoomAtLatLng(googleMaps::LatLng latLng)
{

}

void GoogleMapsPlugin::geocodeName(QString location)
{

}

void GoogleMapsPlugin::geocodeLatLng(googleMaps::LatLng latLng)
{

}

void GoogleMapsPlugin::getElevationAlongPath(googleMaps::PathElevationRequest request)
{

}

void GoogleMapsPlugin::getElevationForLocations(googleMaps::LocationElevationRequest request)
{

}

void GoogleMapsPlugin::messageReceived(const QJsonObject& message)
{

}


