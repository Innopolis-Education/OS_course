# I created image before starting execution of this file
fallocate --length 50M lofs.img
sudo losetup --find
sudo losetup -fP lofs.img
sudo mkfs.fat -F 32 $(sudo losetup -j lofs.img)
sudo mount $(sudo losetup -j lofs.img) ../week11
# sudo umount ../week11
