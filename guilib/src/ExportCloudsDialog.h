/*
Copyright (c) 2010-2014, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EXPORTCLOUDSDIALOG_H_
#define EXPORTCLOUDSDIALOG_H_

#include <QDialog>
#include <QMap>
#include <QtCore/QSettings>

#include <rtabmap/core/Signature.h>
#include <rtabmap/core/Parameters.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>
#include <pcl/TextureMesh.h>
#include <pcl/pcl_base.h>

class Ui_ExportCloudsDialog;
class QAbstractButton;

namespace rtabmap {
class ProgressDialog;

class ExportCloudsDialog : public QDialog
{
	Q_OBJECT

public:
	ExportCloudsDialog(QWidget *parent = 0);

	virtual ~ExportCloudsDialog();

	void saveSettings(QSettings & settings, const QString & group = "") const;
	void loadSettings(QSettings & settings, const QString & group = "");

	void exportClouds(
			const std::map<int, Transform> & poses,
			const std::map<int, int> & mapIds,
			const QMap<int, Signature> & cachedSignatures,
			const std::map<int, std::pair<pcl::PointCloud<pcl::PointXYZRGB>::Ptr, pcl::IndicesPtr> > & createdClouds,
			const QString & workingDirectory,
			const ParametersMap & parameters);

	void viewClouds(
			const std::map<int, Transform> & poses,
			const std::map<int, int> & mapIds,
			const QMap<int, Signature> & cachedSignatures,
			const std::map<int, std::pair<pcl::PointCloud<pcl::PointXYZRGB>::Ptr, pcl::IndicesPtr> > & createdClouds,
			const QString & workingDirectory,
			const ParametersMap & parameters);

signals:
	void configChanged();

public slots:
	void restoreDefaults();

private slots:
	void updateReconstructionFlavor();
	void updateMLSGrpVisibility();

private:
	std::map<int, std::pair<pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr, pcl::IndicesPtr> > getClouds(
			const std::map<int, Transform> & poses,
			const QMap<int, Signature> & cachedSignatures,
			const std::map<int, std::pair<pcl::PointCloud<pcl::PointXYZRGB>::Ptr, pcl::IndicesPtr> > & createdClouds,
			const ParametersMap & parameters) const;
	bool getExportedClouds(
				const std::map<int, Transform> & poses,
				const std::map<int, int> & mapIds,
				const QMap<int, Signature> & cachedSignatures,
				const std::map<int, std::pair<pcl::PointCloud<pcl::PointXYZRGB>::Ptr, pcl::IndicesPtr> > & createdClouds,
				const QString & workingDirectory,
				const ParametersMap & parameters,
				std::map<int, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr> & clouds,
				std::map<int, pcl::PolygonMesh::Ptr> & meshes,
				std::map<int, pcl::TextureMesh::Ptr> & textureMeshes);
	void saveClouds(const QString & workingDirectory, const std::map<int, Transform> & poses, const std::map<int, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr> & clouds, bool binaryMode = true);
	void saveMeshes(const QString & workingDirectory, const std::map<int, Transform> & poses, const std::map<int, pcl::PolygonMesh::Ptr> & meshes, bool binaryMode = true);
	void saveTextureMeshes(const QString & workingDirectory, const std::map<int, Transform> & poses, const std::map<int, pcl::TextureMesh::Ptr> & meshes);

	void setSaveButton();
	void setOkButton();
	void enableRegeneration(bool enabled);

private:
	Ui_ExportCloudsDialog * _ui;
	ProgressDialog * _progressDialog;
};

}

#endif /* EXPORTCLOUDSDIALOG_H_ */
