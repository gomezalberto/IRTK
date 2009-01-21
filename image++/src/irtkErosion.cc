/*=========================================================================

  Library   : Image Registration Toolkit (IRTK)
  Module    : $Id$
  Copyright : Imperial College, Department of Computing
              Visual Information Processing (VIP), 2008 onwards
  Date      : $Date$
  Version   : $Revision$
  Changes   : $Author$

=========================================================================*/

#include <irtkImage.h>

#include <irtkErosion.h>

template <class VoxelType> irtkErosion<VoxelType>::irtkErosion()
{}

template <class VoxelType> irtkErosion<VoxelType>::~irtkErosion(void)
{}

template <class VoxelType> Bool irtkErosion<VoxelType>::RequiresBuffering(void)
{
  return True;
}

template <class VoxelType> const char *irtkErosion<VoxelType>::NameOfClass()
{
  return "irtkErosion";
}

template <class VoxelType> void irtkErosion<VoxelType>::Run()
{
  int i, j, k, x, y, z, t;
  VoxelType value;

  // Do the initial set up
  this->Initialize();

  for (t = 0; t < this->_input->GetT(); t++) {
    for (z = 0; z < this->_input->GetZ(); z++) {
      for (y = 0; y < this->_input->GetY(); y++) {
        for (x = 0; x < this->_input->GetX(); x++) {
          if ((x == 0) || (x == this->_input->GetX()-1) ||
              (y == 0) || (y == this->_input->GetY()-1) ||
              (z == 0) || (z == this->_input->GetZ()-1)) {
            this->_output->Put(x, y, z, t, this->_input->Get(x, y, z, t));
          } else {
            value = this->_input->Get(x, y, z, t);
            for (k = -1; k <= 1; k++) {
              for (j = -1; j <= 1; j++) {
                for (i = -1; i <= 1; i++) {
                  if (this->_input->Get(x+i, y+j, z+k, t) < value)
                    value = this->_input->Get(x+i, y+j, z+k, t);
                }
              }
            }
            this->_output->Put(x, y, z, t, value);
          }
        }
      }
    }
  }

  // Do the final cleaning up
  this->Finalize();
}

template class irtkErosion<irtkBytePixel>;
template class irtkErosion<irtkGreyPixel>;
template class irtkErosion<irtkRealPixel>;