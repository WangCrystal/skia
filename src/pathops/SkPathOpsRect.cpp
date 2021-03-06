/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include "SkPathOpsConic.h"
#include "SkPathOpsCubic.h"
#include "SkPathOpsLine.h"
#include "SkPathOpsQuad.h"
#include "SkPathOpsRect.h"

void SkDRect::setBounds(const SkDQuad& quad) {
    set(quad[0]);
    add(quad[2]);
    double tValues[2];
    int roots = 0;
    if (!between(quad[0].fX, quad[1].fX, quad[2].fX)) {
        roots = SkDQuad::FindExtrema(quad[0].fX, quad[1].fX, quad[2].fX, tValues);
    }
    if (!between(quad[0].fY, quad[1].fY, quad[2].fY)) {
        roots += SkDQuad::FindExtrema(quad[0].fY, quad[1].fY, quad[2].fY, &tValues[roots]);
    }
    for (int x = 0; x < roots; ++x) {
        add(quad.ptAtT(tValues[x]));
    }
}

void SkDRect::setBounds(const SkDConic& conic) {
    set(conic[0]);
    add(conic[2]);
    double tValues[2];
    int roots = 0;
    if (!between(conic[0].fX, conic[1].fX, conic[2].fX)) {
        roots = SkDConic::FindExtrema(&conic[0].fX, conic.fWeight, tValues);
    }
    if (!between(conic[0].fY, conic[1].fY, conic[2].fY)) {
        roots += SkDConic::FindExtrema(&conic[0].fY, conic.fWeight, &tValues[roots]);
    }
    for (int x = 0; x < roots; ++x) {
        add(conic.ptAtT(tValues[x]));
    }
}

static bool is_bounded_by_end_points(double a, double b, double c, double d) {
    return between(a, b, d) && between(a, c, d);
}

void SkDRect::setBounds(const SkDCubic& c) {
    set(c[0]);
    add(c[3]);
    double tValues[4];
    int roots = 0;
    if (!is_bounded_by_end_points(c[0].fX, c[1].fX, c[2].fX, c[3].fX)) {
        roots = SkDCubic::FindExtrema(c[0].fX, c[1].fX, c[2].fX, c[3].fX, tValues);
    }
    if (!is_bounded_by_end_points(c[0].fY, c[1].fY, c[2].fY, c[3].fY)) {
        roots += SkDCubic::FindExtrema(c[0].fY, c[1].fY, c[2].fY, c[3].fY, &tValues[roots]);
    }
    for (int x = 0; x < roots; ++x) {
        add(c.ptAtT(tValues[x]));
    }
}
