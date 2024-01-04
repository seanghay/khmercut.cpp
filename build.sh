#!/usr/bin/env bash

rm -rf bin/khmercut
mkdir -p bin/

g++ -x c liblbfgs/lib/lbfgs.c \
crfsuite/lib/crf/src/crf1d_context.c \
crfsuite/lib/crf/src/crf1d_encode.c \
crfsuite/lib/crf/src/crf1d_feature.c \
crfsuite/lib/crf/src/crf1d_model.c \
crfsuite/lib/crf/src/crf1d_tag.c \
crfsuite/lib/crf/src/crfsuite.c \
crfsuite/lib/crf/src/crfsuite_train.c \
crfsuite/lib/crf/src/dataset.c \
crfsuite/lib/crf/src/dictionary.c \
crfsuite/lib/crf/src/holdout.c \
crfsuite/lib/crf/src/logging.c \
crfsuite/lib/crf/src/params.c \
crfsuite/lib/crf/src/quark.c \
crfsuite/lib/crf/src/rumavl.c \
crfsuite/lib/crf/src/train_arow.c \
crfsuite/lib/crf/src/train_averaged_perceptron.c \
crfsuite/lib/crf/src/train_l2sgd.c \
crfsuite/lib/crf/src/train_lbfgs.c \
crfsuite/lib/crf/src/train_passive_aggressive.c \
crfsuite/lib/cqdb/src/cqdb.c \
crfsuite/lib/cqdb/src/lookup3.c \
-I liblbfgs/include \
-I crfsuite/include \
-I crfsuite/lib/cqdb/include \
-x c++ main.cc -O3 -o bin/khmercut -w
