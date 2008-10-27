#!/bin/bash
xsd cxx-tree --generate-serialization --root-element mtp2lastfm \
	--output-dir . --namespace-map =xml  --hxx-suffix .h --cxx-suffix .cpp \
	mtp2lastfm.xsd
