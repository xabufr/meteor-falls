
SRC = ../src/ozcollide/aabbtree.cpp \
          ../src/ozcollide/aabbtree_aabb.cpp \
          ../src/ozcollide/aabbtree_poly.cpp \
          ../src/ozcollide/aabbtree_sphere.cpp \
          ../src/ozcollide/aabbtreeaabb_builder.cpp \
          ../src/ozcollide/aabbtreepoly_builder.cpp \
          ../src/ozcollide/aabbtreesphere_builder.cpp \
          ../src/ozcollide/box.cpp \
          ../src/ozcollide/dataio.cpp \
          ../src/ozcollide/dist_pointbox.cpp \
          ../src/ozcollide/dist_pointline.cpp \
          ../src/ozcollide/ellipsoid.cpp \
          ../src/ozcollide/frustum.cpp \
          ../src/ozcollide/intr_boxbox.cpp \
          ../src/ozcollide/intr_frustumsphere.cpp \
          ../src/ozcollide/intr_linebox.cpp \
          ../src/ozcollide/intr_lineline.cpp \
          ../src/ozcollide/intr_segmenttri.cpp \
          ../src/ozcollide/intr_spherebox.cpp \
          ../src/ozcollide/intr_sphereline.cpp \
          ../src/ozcollide/intr_tribox.cpp \
          ../src/ozcollide/intr_tripoint.cpp \
          ../src/ozcollide/matrix.cpp \
          ../src/ozcollide/obb.cpp \
          ../src/ozcollide/ozcollide.cpp \
          ../src/ozcollide/plane.cpp \
          ../src/ozcollide/polygon.cpp \
          ../src/ozcollide/sphere.cpp \
          ../src/ozcollide/vec2f.cpp \
          ../src/ozcollide/vec3f.cpp \
          ../src/ozcollide/vector.cpp

OBJ = $(SRC:.cpp=.o)
OUT = libozcollide.a
INCLUDES = -I ../include
CCFLAGS = -g
CCC = g++

default:  $(OUT)

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
clean:
	rm ../src/ozcollide/*.o
install:
	cp $(OUT) /usr/lib/$(OUT)