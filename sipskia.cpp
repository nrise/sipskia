#include "SkCanvas.h"
#include "SkCommandLineFlags.h"
#include "SkData.h"
#include "SkDocument.h"
#include "SkGraphics.h"
#include "SkSurface.h"
#include "SkImage.h"
#include "SkImageFilter.h"
#include "SkStream.h"
#include "SkString.h"
#include "SkPaint.h"
#include "SkImageGenerator.h"

#include <boost/python.hpp>
#include <stdexcept>

#ifdef SIPSKIA_BGRA
#define SIPSKIA_COLORTYPE kBGRA_8888_SkColorType
#else
#define SIPSKIA_COLORTYPE kN32_SkColorType
#endif

boost::python::object convert_webp(PyObject* raw, long canvasSize, int quality) {
	int size =  Py_SIZE(raw);
	void* data = (void*)PyBytes_AsString(raw);

	sk_sp<SkData> skdata(SkData::MakeWithoutCopy(data, size));
	if(!data) return boost::python::object();
	sk_sp<SkImage> image = SkImage::MakeFromEncoded(skdata);
	if(!image) return boost::python::object();

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	float left = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	float bottom = 0.0f;

	int imageWidth = image->width();
	int imageHeight = image->height();

	if(imageWidth > imageHeight) {
		top = 0.0f;
		bottom = imageHeight;
		left = (imageWidth - imageHeight)/2.0f;
		right = left + imageHeight;
	}else{
		left = 0.0f;
		right = imageWidth;
		top = (imageHeight - imageWidth)/2.0f;
		bottom = top + imageWidth;
	}

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvasSize, canvasSize, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	
	canvas->drawImageRect(image, SkRect::MakeLTRB(left, top, right, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvasSize, canvasSize), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());

	if(!img) return boost::python::object();
	sk_sp<SkData> webp(img->encodeToData(SkEncodedImageFormat::kWEBP, quality));
	if(!webp) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyBytes_FromStringAndSize((char*)webp->data(), webp->size())));
}

boost::python::object convert_jpg(PyObject* raw, long canvasSize, int quality) {
	int size =  Py_SIZE(raw);
	void* data = (void*)PyBytes_AsString(raw);

	// SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy(data, size));
	if(!data) return boost::python::object();
	sk_sp<SkImage> image = SkImage::MakeFromEncoded(skdata);
	if(!image) return boost::python::object();

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

    long canvasHeight = (long)((image->height() * canvasSize) / image->width());
    if(canvasHeight < 1){
        canvasHeight = 1;
    }

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvasSize, canvasHeight, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawImageRect(image, SkRect::MakeLTRB(0.0f, 0.0f, image->width(), image->height()), SkRect::MakeXYWH(0.0f, 0.0f, canvasSize, canvasHeight), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encodeToData(SkEncodedImageFormat::kJPEG, quality));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyBytes_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

boost::python::object convert_origin_webp(PyObject* raw, int quality) {
	int size =  Py_SIZE(raw);
	void* data = (void*)PyBytes_AsString(raw);

	sk_sp<SkData> skdata(SkData::MakeWithoutCopy(data, size));
	if(!data) return boost::python::object();
	sk_sp<SkImage> image = SkImage::MakeFromEncoded(skdata);
	if(!image) return boost::python::object();

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	float canvasWidth = image->width();
	float canvasHeight = image->height();
	
	float left = 0.0f;
	float right = canvasWidth;
	float top = 0.0f;
	float bottom = canvasHeight;

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvasWidth, canvasHeight, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawImageRect(image, SkRect::MakeLTRB(left, top, right, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvasWidth, canvasHeight), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> webp(img->encodeToData(SkEncodedImageFormat::kWEBP, quality));
	if(!webp) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyBytes_FromStringAndSize((char*)webp->data(), webp->size())));
}

boost::python::object convert_origin_jpg(PyObject* raw, int quality) {
	int size =  Py_SIZE(raw);
	void* data = (void*)PyBytes_AsString(raw);

	sk_sp<SkData> skdata(SkData::MakeWithoutCopy(data, size));
	if(!data) return boost::python::object();
	sk_sp<SkImage> image = SkImage::MakeFromEncoded(skdata);
	if(!image) return boost::python::object();

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	float canvasWidth = image->width();
	float canvasHeight = image->height();

	float left = 0.0f;
	float right = canvasWidth;
	float top = 0.0f;
	float bottom = canvasHeight;

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvasWidth, canvasHeight, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawImageRect(image, SkRect::MakeLTRB(left, top, right, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvasWidth, canvasHeight), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> webp(img->encodeToData(SkEncodedImageFormat::kJPEG, quality));
	if(!webp) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyBytes_FromStringAndSize((char*)webp->data(), webp->size())));
}

boost::python::object convert_with_crop_jpg(PyObject* raw, long cropWidth, long cropHeight, long canvasWidth, long canvasHeight, int quality) {
	int size =  Py_SIZE(raw);
	void* data = (void*)PyBytes_AsString(raw);

	sk_sp<SkData> skdata(SkData::MakeWithoutCopy(data, size));
	if(!data) return boost::python::object();
	sk_sp<SkImage> image = SkImage::MakeFromEncoded(skdata);
	if(!image) return boost::python::object();

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	float width = cropWidth;
	float height = cropHeight;
	float top = image->height() / 2.0f - height / 2.0f;
	float bottom = top + height;

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvasWidth, canvasHeight, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawImageRect(image, SkRect::MakeLTRB(0, top, width, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvasWidth, canvasHeight), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> webp(img->encodeToData(SkEncodedImageFormat::kJPEG, quality));
	if(!webp) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyBytes_FromStringAndSize((char*)webp->data(), webp->size())));
}


using namespace boost::python;
BOOST_PYTHON_MODULE(sipskia)
{
	def("convert_webp", &convert_webp);
	def("convert_jpg", &convert_jpg);
	def("convert_origin_webp", &convert_origin_webp);
	def("convert_origin_jpg", &convert_origin_jpg);
	def("convert_with_crop_jpg", &convert_with_crop_jpg);
}

