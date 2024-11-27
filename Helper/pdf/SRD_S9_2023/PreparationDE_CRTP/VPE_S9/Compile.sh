gcc -o ../bin/EdGradientKirsh4SepMasksThrThi EdGradientKirsh4SepMasksThrThi.c EdLibGradientKirsh4SepMasks.c EdUtilities.c EdLibEdgeUtilities.c EdLibThreshold.c EdLibThinning.c

echo "Compilation Sep Masks OK"

gcc -o ../bin/EdGradientKirsh4GathMasksThrThi EdGradientKirsh4GathMasksThrThi.c EdLibGradientKirsh4GathMasks.c EdUtilities.c EdLibEdgeUtilities.c EdLibThreshold.c EdLibThinning.c

echo "Compilation Gath Masks OK"

gcc -o ../bin/EdRVBGradientThrThi EdRVBGradientThrThi.c EdLibRVBGradientThrThi.c EdUtilities.c EdLibEdgeUtilities.c EdLibThreshold.c EdLibThinning.c

echo "Compilation RVB Gath Masks OK"
