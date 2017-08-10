#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/dir_nav.h>


using namespace dlib;
using namespace std;

int main(int argc, char** argv) try
{
	if (argc != 2)
	{
		cout << "Call this program like this: " << endl;
		cout << "./video_tracking_ex ../video_frames" << endl;
		return 1;
	}

	// Get the list of video frames.  
	std::vector<file> files = get_files_in_directory_tree(argv[1], match_ending(".jpg"));
	/*динамический массив, состо€щий из картинок из видео.
	функци€ get_files_in_directory_tree(argv[1], match_ending(".jpg")) 
	находит файлы с расширением .jpg в директории, указанной в переменной argv[1]
	*/
	std::sort(files.begin(), files.end()); // функци€ sort() сортирует все изображени€ в заданном диапазоне
	if (files.size() == 0)
	{
		cout << "No images found in " << argv[1] << endl;
		return 1;
	}

	// загрузка первого кадра в массив пикселей array2d.  
	array2d<unsigned char> img;
	load_image(img, files[0]); // Ёта глобальна€ функци€ принимает им€ файла,
	//смотрит на его расширение и затем загружает его в массив2d пикселей, 
	//использу€ соответствующую процедуру загрузки изображени€.

	// Now create a tracker and start a track on the juice box.  If you look at the first
	// frame you will see that the juice box is centered at pixel point(92,110) and 38
	// pixels wide and 86 pixels tall.
	correlation_tracker tracker;
	tracker.start_track(img, centered_rect(point(333, 265), 136, 320));//координаты объекта на первом кадре

	// Now run the tracker.  All we have to do is call tracker.update() and it will keep
	// track of the juice box!
	image_window win; // контейнер дл€ изображени€ (существует дл€ упрощени€ загрузки изображени€ на экран)
	for (unsigned long i = 1; i < files.size(); ++i)
	{
		load_image(img, files[i]);
		tracker.update(img);

		win.set_image(img);
		win.clear_overlay();
		win.add_overlay(tracker.get_position());

		sleep(3);
		continue;
		
	}
}
catch (std::exception& e)
{
	cout << e.what() << endl;
}

