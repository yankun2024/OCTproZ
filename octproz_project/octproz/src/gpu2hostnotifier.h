/**
**  This file is part of OCTproZ.
**  OCTproZ is an open source software for processig of optical
**  coherence tomography (OCT) raw data.
**  Copyright (C) 2019-2022 Miroslav Zabic
**
**  OCTproZ is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see http://www.gnu.org/licenses/.
**
****
** Author:	Miroslav Zabic
** Contact:	zabic
**			at
**			spectralcode.de
****
**/

#ifndef GPU2HOSTNOTIFIER_H
#define GPU2HOSTNOTIFIER_H


#include <QObject>
#include "octalgorithmparameters.h"
#include "cuda_runtime_api.h"
#include "helper_cuda.h"



class Gpu2HostNotifier : public QObject
{
	Q_OBJECT

public:
	static Gpu2HostNotifier* getInstance(QObject* parent = nullptr);
	~Gpu2HostNotifier();

	static void CUDART_CB dh2StreamingCallback(void* currStreamingBuffer);
	static void CUDART_CB backgroundSignalCallback(void* backgroundSignal);

private:
	Gpu2HostNotifier(QObject *parent);
	static Gpu2HostNotifier* gpu2hostNotifier;

public slots:
	void emitCurrentStreamingBuffer(void* currStreamingBuffer);
	void emitBackgroundRecorded();

signals:
	void processedRecordDone(void* recordBuffer);
	void newGpuDataAvailible(void* rawBuffer, unsigned bitDepth, unsigned int samplesPerLine, unsigned int linesPerFrame, unsigned int framesPerBuffer, unsigned int buffersPerVolume, unsigned int currentBufferNr);
	void backgroundRecorded();
};


#endif //GPU2HOSTNOTIFIER_H
