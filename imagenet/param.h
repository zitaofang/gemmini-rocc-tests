static const struct ConvParams conv_1_params = {.batch_size=4, .in_dim=224, .kernel_size=3, .in_channels=3, .out_channels=32, .stride=2, .padding=1, .bias=1, .depthwise=0, .out_dim=112, .n_patches=50176, .patch_size=27, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=112, .output_scale=7, .I=50176, .J=32, .K=27, .res_scale=0};
static const struct ConvParams conv_dw_2_params = {.batch_size=4, .in_dim=112, .kernel_size=3, .in_channels=32, .out_channels=32, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=112, .n_patches=50176, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=112, .output_scale=6, .res_scale=0, .I=50176, .J=32};
static const struct ConvParams conv_3_params = {.batch_size=4, .in_dim=112, .kernel_size=1, .in_channels=32, .out_channels=16, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=112, .n_patches=50176, .patch_size=32, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=112, .output_scale=5, .I=50176, .J=16, .K=32, .res_scale=0};
static const struct ConvParams conv_4_params = {.batch_size=4, .in_dim=112, .kernel_size=1, .in_channels=16, .out_channels=96, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=112, .n_patches=50176, .patch_size=16, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=112, .output_scale=7, .I=50176, .J=96, .K=16, .res_scale=0};
static const struct ConvParams conv_dw_5_params = {.batch_size=4, .in_dim=112, .kernel_size=3, .in_channels=96, .out_channels=96, .stride=2, .padding=1, .bias=1, .depthwise=1, .out_dim=56, .n_patches=12544, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=4, .res_scale=0, .I=12544, .J=96};
static const struct ConvParams conv_6_params = {.batch_size=4, .in_dim=56, .kernel_size=1, .in_channels=96, .out_channels=24, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=56, .n_patches=12544, .patch_size=96, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=6, .I=12544, .J=24, .K=96, .res_scale=0};
static const struct ConvParams conv_7_params = {.batch_size=4, .in_dim=56, .kernel_size=1, .in_channels=24, .out_channels=144, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=56, .n_patches=12544, .patch_size=24, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=7, .I=12544, .J=144, .K=24, .res_scale=1};
static const struct ConvParams conv_dw_8_params = {.batch_size=4, .in_dim=56, .kernel_size=3, .in_channels=144, .out_channels=144, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=56, .n_patches=12544, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=5, .res_scale=1, .I=12544, .J=144};
static const struct ConvParams conv_9_params = {.batch_size=4, .in_dim=56, .kernel_size=1, .in_channels=144, .out_channels=24, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=56, .n_patches=12544, .patch_size=144, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=7, .I=12544, .J=24, .K=144, .res_scale=1};
static const struct ConvParams conv_10_params = {.batch_size=4, .in_dim=56, .kernel_size=1, .in_channels=24, .out_channels=144, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=56, .n_patches=12544, .patch_size=24, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=56, .output_scale=6, .I=12544, .J=144, .K=24, .res_scale=1};
static const struct ConvParams conv_dw_11_params = {.batch_size=4, .in_dim=56, .kernel_size=3, .in_channels=144, .out_channels=144, .stride=2, .padding=1, .bias=1, .depthwise=1, .out_dim=28, .n_patches=3136, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=4, .res_scale=1, .I=3136, .J=144};
static const struct ConvParams conv_12_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=144, .out_channels=32, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=144, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=8, .I=3136, .J=32, .K=144, .res_scale=1};
static const struct ConvParams conv_13_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=32, .out_channels=192, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=32, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=7, .I=3136, .J=192, .K=32, .res_scale=0};
static const struct ConvParams conv_dw_14_params = {.batch_size=4, .in_dim=28, .kernel_size=3, .in_channels=192, .out_channels=192, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=28, .n_patches=3136, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=5, .res_scale=0, .I=3136, .J=192};
static const struct ConvParams conv_15_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=192, .out_channels=32, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=192, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=8, .I=3136, .J=32, .K=192, .res_scale=0};
static const struct ConvParams conv_16_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=32, .out_channels=192, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=32, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=7, .I=3136, .J=192, .K=32, .res_scale=0};
static const struct ConvParams conv_dw_17_params = {.batch_size=4, .in_dim=28, .kernel_size=3, .in_channels=192, .out_channels=192, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=28, .n_patches=3136, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=5, .res_scale=0, .I=3136, .J=192};
static const struct ConvParams conv_18_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=192, .out_channels=32, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=192, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=8, .I=3136, .J=32, .K=192, .res_scale=0};
static const struct ConvParams conv_19_params = {.batch_size=4, .in_dim=28, .kernel_size=1, .in_channels=32, .out_channels=192, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=28, .n_patches=3136, .patch_size=32, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=28, .output_scale=8, .I=3136, .J=192, .K=32, .res_scale=0};
static const struct ConvParams conv_dw_20_params = {.batch_size=4, .in_dim=28, .kernel_size=3, .in_channels=192, .out_channels=192, .stride=2, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=5, .res_scale=0, .I=784, .J=192};
static const struct ConvParams conv_21_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=192, .out_channels=64, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=192, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=64, .K=192, .res_scale=0};
static const struct ConvParams conv_22_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=64, .out_channels=384, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=64, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=8, .I=784, .J=384, .K=64, .res_scale=0};
static const struct ConvParams conv_dw_23_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=384, .out_channels=384, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=4, .res_scale=0, .I=784, .J=384};
static const struct ConvParams conv_24_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=384, .out_channels=64, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=384, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=8, .I=784, .J=64, .K=384, .res_scale=0};
static const struct ConvParams conv_25_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=64, .out_channels=384, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=64, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=9, .I=784, .J=384, .K=64, .res_scale=0};
static const struct ConvParams conv_dw_26_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=384, .out_channels=384, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=3, .res_scale=0, .I=784, .J=384};
static const struct ConvParams conv_27_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=384, .out_channels=64, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=384, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=8, .I=784, .J=64, .K=384, .res_scale=0};
static const struct ConvParams conv_28_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=64, .out_channels=384, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=64, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=9, .I=784, .J=384, .K=64, .res_scale=1};
static const struct ConvParams conv_dw_29_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=384, .out_channels=384, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=6, .res_scale=1, .I=784, .J=384};
static const struct ConvParams conv_30_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=384, .out_channels=64, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=384, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=64, .K=384, .res_scale=1};
static const struct ConvParams conv_31_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=64, .out_channels=384, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=64, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=384, .K=64, .res_scale=1};
static const struct ConvParams conv_dw_32_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=384, .out_channels=384, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=5, .res_scale=1, .I=784, .J=384};
static const struct ConvParams conv_33_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=384, .out_channels=96, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=384, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=96, .K=384, .res_scale=1};
static const struct ConvParams conv_34_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=96, .out_channels=576, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=96, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=8, .I=784, .J=576, .K=96, .res_scale=1};
static const struct ConvParams conv_dw_35_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=576, .out_channels=576, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=5, .res_scale=1, .I=784, .J=576};
static const struct ConvParams conv_36_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=576, .out_channels=96, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=576, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=96, .K=576, .res_scale=1};
static const struct ConvParams conv_37_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=96, .out_channels=576, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=96, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=9, .I=784, .J=576, .K=96, .res_scale=1};
static const struct ConvParams conv_dw_38_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=576, .out_channels=576, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=14, .n_patches=784, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=3, .res_scale=1, .I=784, .J=576};
static const struct ConvParams conv_39_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=576, .out_channels=96, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=576, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=7, .I=784, .J=96, .K=576, .res_scale=1};
static const struct ConvParams conv_40_params = {.batch_size=4, .in_dim=14, .kernel_size=1, .in_channels=96, .out_channels=576, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=14, .n_patches=784, .patch_size=96, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=14, .output_scale=8, .I=784, .J=576, .K=96, .res_scale=1};
static const struct ConvParams conv_dw_41_params = {.batch_size=4, .in_dim=14, .kernel_size=3, .in_channels=576, .out_channels=576, .stride=2, .padding=1, .bias=1, .depthwise=1, .out_dim=7, .n_patches=196, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=5, .res_scale=1, .I=196, .J=576};
static const struct ConvParams conv_42_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=576, .out_channels=160, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=576, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=9, .I=196, .J=160, .K=576, .res_scale=1};
static const struct ConvParams conv_43_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=160, .out_channels=960, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=160, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=7, .I=196, .J=960, .K=160, .res_scale=1};
static const struct ConvParams conv_dw_44_params = {.batch_size=4, .in_dim=7, .kernel_size=3, .in_channels=960, .out_channels=960, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=7, .n_patches=196, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=3, .res_scale=1, .I=196, .J=960};
static const struct ConvParams conv_45_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=960, .out_channels=160, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=960, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=10, .I=196, .J=160, .K=960, .res_scale=1};
static const struct ConvParams conv_46_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=160, .out_channels=960, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=160, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=7, .I=196, .J=960, .K=160, .res_scale=1};
static const struct ConvParams conv_dw_47_params = {.batch_size=4, .in_dim=7, .kernel_size=3, .in_channels=960, .out_channels=960, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=7, .n_patches=196, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=5, .res_scale=1, .I=196, .J=960};
static const struct ConvParams conv_48_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=960, .out_channels=160, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=960, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=9, .I=196, .J=160, .K=960, .res_scale=1};
static const struct ConvParams conv_49_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=160, .out_channels=960, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=160, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=6, .I=196, .J=960, .K=160, .res_scale=1};
static const struct ConvParams conv_dw_50_params = {.batch_size=4, .in_dim=7, .kernel_size=3, .in_channels=960, .out_channels=960, .stride=1, .padding=1, .bias=1, .depthwise=1, .out_dim=7, .n_patches=196, .patch_size=9, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=2, .res_scale=1, .I=196, .J=960};
static const struct ConvParams conv_51_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=960, .out_channels=320, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=960, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=6, .I=196, .J=320, .K=960, .res_scale=1};
static const struct ConvParams conv_52_params = {.batch_size=4, .in_dim=7, .kernel_size=1, .in_channels=320, .out_channels=1280, .stride=1, .padding=0, .bias=1, .depthwise=0, .out_dim=7, .n_patches=196, .patch_size=320, .pool_size=1, .pool_stride=1, .pool_padding=0, .out_dim_pooled=7, .output_scale=8, .I=196, .J=1280, .K=320, .res_scale=1};