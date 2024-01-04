cmake_minimum_required(VERSION 3.8)

project(khmercut)
enable_language(C)

set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} src/main.cc src/khmercut.cc
  liblbfgs/lib/lbfgs.c
  crfsuite/lib/crf/src/crf1d_context.c
  crfsuite/lib/crf/src/crf1d_encode.c
  crfsuite/lib/crf/src/crf1d_feature.c
  crfsuite/lib/crf/src/crf1d_model.c
  crfsuite/lib/crf/src/crf1d_tag.c
  crfsuite/lib/crf/src/crfsuite.c
  crfsuite/lib/crf/src/crfsuite_train.c
  crfsuite/lib/crf/src/dataset.c
  crfsuite/lib/crf/src/dictionary.c
  crfsuite/lib/crf/src/holdout.c
  crfsuite/lib/crf/src/logging.c
  crfsuite/lib/crf/src/params.c
  crfsuite/lib/crf/src/quark.c
  crfsuite/lib/crf/src/rumavl.c
  crfsuite/lib/crf/src/train_arow.c
  crfsuite/lib/crf/src/train_averaged_perceptron.c
  crfsuite/lib/crf/src/train_l2sgd.c
  crfsuite/lib/crf/src/train_lbfgs.c
  crfsuite/lib/crf/src/train_passive_aggressive.c
  crfsuite/lib/cqdb/src/cqdb.c
  crfsuite/lib/cqdb/src/lookup3.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
  liblbfgs/include
  crfsuite/lib/cqdb/include 
  crfsuite/include
  utfcpp/source
)

