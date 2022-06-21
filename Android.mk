LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# orbslam3.so

LOCAL_CPP_EXTENSION := .cpp .cc .ipp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/include/ORB_SLAM3 \
    $(LOCAL_PATH)/include/ORB_SLAM3/CameraModels \
    $(LOCAL_PATH)/../include \
    $(LOCAL_PATH)/../include/eigen3 \
    $(LOCAL_PATH)/Thirdparty/Sophus \
    $(LOCAL_PATH)/../boost/include/boost-1_74 \

LOCAL_SRC_FILES := \
    src/System.cc \
    src/Tracking.cc \
    src/LocalMapping.cc \
    src/LoopClosing.cc \
    src/ORBextractor.cc \
    src/ORBmatcher.cc \
    src/FrameDrawer.cc \
    src/Converter.cc \
    src/MapPoint.cc \
    src/KeyFrame.cc \
    src/Atlas.cc \
    src/Map.cc \
    src/Optimizer.cc \
    src/Frame.cc \
    src/KeyFrameDatabase.cc \
    src/Sim3Solver.cc \
    src/ImuTypes.cc \
    src/G2oTypes.cc \
    src/CameraModels/Pinhole.cpp \
    src/CameraModels/KannalaBrandt8.cpp \
    src/OptimizableTypes.cpp \ \
    src/MLPnPsolver.cpp \
    src/GeometricTools.cc \
    src/TwoViewReconstruction.cc \
    src/Config.cc \
    src/Settings.cc

LOCAL_SRC_FILES += \
    src/md5.c

LOCAL_SRC_FILES += \
    Thirdparty/DBoW2/DBoW2/BowVector.cpp \
    Thirdparty/DBoW2/DBoW2/FeatureVector.cpp \
    Thirdparty/DBoW2/DBoW2/FORB.cpp \
    Thirdparty/DBoW2/DBoW2/ScoringObject.cpp \
    Thirdparty/DBoW2/DUtils/Random.cpp \
    Thirdparty/DBoW2/DUtils/Timestamp.cpp

LOCAL_SRC_FILES += \
    Thirdparty/g2o/g2o/types/types_sba.cpp \
    Thirdparty/g2o/g2o/types/types_six_dof_expmap.cpp \
    Thirdparty/g2o/g2o/types/types_seven_dof_expmap.cpp \
    Thirdparty/g2o/g2o/core/hyper_graph_action.cpp \
    Thirdparty/g2o/g2o/core/hyper_graph.cpp \
    Thirdparty/g2o/g2o/core/marginal_covariance_cholesky.cpp \
    Thirdparty/g2o/g2o/core/matrix_structure.cpp \
    Thirdparty/g2o/g2o/core/batch_stats.cpp \
    Thirdparty/g2o/g2o/core/parameter.cpp \
    Thirdparty/g2o/g2o/core/cache.cpp \
    Thirdparty/g2o/g2o/core/optimizable_graph.cpp \
    Thirdparty/g2o/g2o/core/solver.cpp \
    Thirdparty/g2o/g2o/core/optimization_algorithm_factory.cpp \
    Thirdparty/g2o/g2o/core/estimate_propagator.cpp \
    Thirdparty/g2o/g2o/core/factory.cpp \
    Thirdparty/g2o/g2o/core/sparse_optimizer.cpp \
    Thirdparty/g2o/g2o/core/hyper_dijkstra.cpp \
    Thirdparty/g2o/g2o/core/parameter_container.cpp \
    Thirdparty/g2o/g2o/core/optimization_algorithm.cpp \
    Thirdparty/g2o/g2o/core/optimization_algorithm_with_hessian.cpp \
    Thirdparty/g2o/g2o/core/optimization_algorithm_levenberg.cpp \
    Thirdparty/g2o/g2o/core/optimization_algorithm_gauss_newton.cpp \
    Thirdparty/g2o/g2o/core/jacobian_workspace.cpp \
    Thirdparty/g2o/g2o/core/robust_kernel.cpp \
    Thirdparty/g2o/g2o/core/robust_kernel_factory.cpp \
    Thirdparty/g2o/g2o/core/robust_kernel_impl.cpp \
    Thirdparty/g2o/g2o/stuff/timeutil.cpp \
    Thirdparty/g2o/g2o/stuff/os_specific.c \
    Thirdparty/g2o/g2o/stuff/string_tools.cpp \
    Thirdparty/g2o/g2o/stuff/property.cpp

# LOCAL_SRC_FILES += \
#     ../boost/include/boost-1_74/boost/archive/impl/text_iarchive_impl.ipp \

LOCAL_CFLAGS += \
    -Wno-undef \
    -Wno-unused-parameter \
    -Wno-reorder-ctor \
    -Wno-delete-abstract-non-virtual-dtor \
    -Wno-delete-non-abstract-non-virtual-dtor \
    -Wno-shadow \
    -Wno-sign-compare \
    -Wno-deprecated-copy \
    -Wno-deprecated-declarations \
    -Wno-unused-variable \
    -Wno-unused-function \
    -Wno-unused-but-set-variable \
    -Wno-missing-prototypes \

LOCAL_SHARED_LIBRARIES += \
    opencv_core \
    opencv_features2d \
    opencv_imgproc \
    opencv_calib3d \

LOCAL_STATIC_LIBRARIES += \
    boost_system \
    boost_serialization \
    opencv_core \
    opencv_features2d \

LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/include/ORB_SLAM3/CameraModels \
    $(LOCAL_PATH)/../include/eigen3 \
    $(LOCAL_PATH)/Thirdparty/Sophus \
    $(LOCAL_PATH)/include

LOCAL_EXPORT_LDLIBS := \
    -llog \

LOCAL_CPP_FEATURES := \
    exceptions \
    rtti \

LOCAL_ARM_MODE := arm

LOCAL_MODULE := orbslam3

# include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
