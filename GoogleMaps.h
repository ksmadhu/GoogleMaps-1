/*
 *
 *  Needs to expose all the signals and slots from MapViewer
 *
 *
 *
 */

#ifndef GOOGLEMAPS_H
#define GOOGLEMAPS_H

#include <QObject>
#include <QWebChannelAbstractTransport>
#include <QWebChannel>
#include "GeocoderRequest.h"
#include "GeocoderComponentRestrictions.h"
#include "GeocoderAddressComponent.h"
#include "GeocoderGeometry.h"
#include "SphericalGeometry.h"
#include "MaxZoomService.h"
#include "Geocoder.h"
#include "SphericalGeometry.h"
#include "MaxZoomService.h"
#include "ElevationService.h"
#include "LatLng.h"
#include "GeocoderResult.h"
#include "ElevationResult.h"

namespace googleMaps
{
    class GoogleMaps;
}


namespace googleMaps
{
    class GoogleMaps : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QWebChannel* channel READ getChannel WRITE setChannel NOTIFY transportReady)
        Q_PROPERTY(bool connectionMade READ isConnected NOTIFY transportReady)
        Q_PROPERTY(QVariantList geocoderResults READ getGeoCoderResults NOTIFY geoLocationsReceived)

    public:
        explicit GoogleMaps(QObject *parent = 0);
        ~GoogleMaps();

        QWebChannel* getChannel() const;
        void setChannel(QWebChannel *chnl);
        bool isConnected();
        QVariantList getGeoCoderResults();

    protected:
        googleMaps::Geocoder* m_geoCoder;
        googleMaps::SphericalGeometry* m_sphericalGeometryService;
        googleMaps::MaxZoomService* m_maxZoomService;
        googleMaps::ElevationService* m_elevationService;
        QWebChannel* m_channel;
        bool m_transportReady;



    signals:
            void distanceResultsReceived(qreal distance);
            void positionResultsReceived(googleMaps::LatLng position);
            void maxZoomReceived(qreal zoomLevel);
            void elevationResultsReceived(QList<googleMaps::ElevationResult> results);
            void sendMessage(const QJsonObject &message);
            void geoLocationsReceived();
            void transportReady();

    public slots:
            /// <summary>
            ///
            /// Return Value:  number
            /// Return unit: meters
            /// Returns the area of a closed path. The computed area uses the same units as the radius. The radius defaults to the Earth's radius in meters, in which case the area is in square meters.
            /// </summary>
            void computeArea(const QList<googleMaps::LatLng>& path);

            /// <summary>
            ///
            /// Return Value:  number
            /// Returns the distance, in meters, between two LatLngs. You can optionally specify a custom radius. The radius defaults to the radius of the Earth.
            /// </summary>
            void computeDistanceBetween(const googleMaps::LatLng& from, const googleMaps::LatLng& to);

            /// <summary>
            ///
            /// Return Value:  number
            /// Returns the heading from one LatLng to another LatLng. Headings are expressed in degrees clockwise from North within the range [-180,180).
            /// </summary>
            void computeHeading(const googleMaps::LatLng& from, const googleMaps::LatLng& to);

            /// <summary>
            ///
            /// Return Value:  number
            /// Returns the length of the given path.
            /// </summary>
            void computeLength(const QList<googleMaps::LatLng>& path);

            /// <summary>
            ///
            /// Return Value:  LatLng
            /// Returns the LatLng resulting from moving a distance from an origin in the specified heading (expressed in degrees clockwise from north).
            /// </summary>
            void computeOffset(const googleMaps::LatLng& from, const qreal& distance, const qreal& heading);

            /// <summary>
            /// Returns the location of origin when provided with a LatLng destination, meters travelled and original heading. Headings are expressed in degrees clockwise from North. This function returns null when no solution is available.
            /// </summary>
            void computeOffsetOrigin(const googleMaps::LatLng& to, const qreal& distance, const qreal& heading);

            /// <summary>
            /// Returns the LatLng which lies the given fraction of the way between the origin LatLng and the destination LatLng.
            /// </summary>
            void interpolate(googleMaps::LatLng& from, googleMaps::LatLng& to, qreal& fraction);
            void getMaxZoomAtLatLng(googleMaps::LatLng latLng);
            void geocodeName(QString location);
            void geocodeLatLng(googleMaps::LatLng latLng);
            void getElevationAlongPath(googleMaps::PathElevationRequest request);
            void getElevationForLocations(googleMaps::LocationElevationRequest request);
            void messageReceived(const QJsonObject& message);
            void handleGeocoderResults(QVariantList results, QString &status);
            void handleDistanceResults(qreal distance);
            void handlePositionResults(googleMaps::LatLng position);
            void handleMaxZoomResults(googleMaps::MaxZoomResult result, int status);
            void handleElevationResults(QList<googleMaps::ElevationResult> results, int status);


    private slots:
        //void handleTransportReady();
        void handleGeoLocationReceived(googleMaps::GeocoderResult& result);
        void handleSelectGeoLocationRequest(QList<googleMaps::GeocoderResult>& results);
        void handleAreaComputed(qreal area);
        void handleHeadingComputed(qreal heding);
        void handleDistanceComputed(qreal distance);
        void handleLengthComputed(qreal length);
        void handleOffsetComputed(googleMaps::LatLng offset);
        void handleOffsetOriginComputed(googleMaps::LatLng offsetOrigin);
        void handlePositionInterpolated(googleMaps::LatLng originOffset);
        void handleMaxZoomReceived(qreal zoomLevel);


    };
}
#endif // GOOGLEMAPS_H