#include <opencv/cvaux.h>
#include <opencv/highgui.h> // Permite abrir las ventanas
#include <opencv/cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main(int argc, char*argv[]){
	IplImage *imagenCamara;
	int r=0,g=255,b=0;
	CvCapture *capturaImagen;
	char charcheckforkeypress;
	capturaImagen = cvCaptureFromCAM(0);
	int step,i=2,j=2;
	if(!capturaImagen){
	    cout << "Error con la imagen de la camara";
		getchar();
		return(-1);
	}

	cvNamedWindow("Ventana", 1);
	while(1){
		imagenCamara = cvQueryFrame(capturaImagen);
		if(!imagenCamara){
			cout << "Error con el frame" << endl;
			getchar();
			break;
		}
		step = imagenCamara->widthStep/sizeof(uchar);
		for(int i = 0; i < imagenCamara->height; i++){
			for(int j = 0; j < imagenCamara->width; j++){
				if(imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 0] >= 0 && imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 0] <= 100 &&
				   imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 1] >= 0 && imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 1] <= 100 &&	
				   imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 2] >= 0 && imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 2] <= 100 ){  
					   imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 2] = r;   //Rojo
					   imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 1] = g;   //Verde
					   imagenCamara->imageData[i*step+j*imagenCamara->nChannels + 0] = b;   //Azul
				}
			}
		}

		cvShowImage("Ventana",imagenCamara);
		charcheckforkeypress = cvWaitKey(20);
		if(charcheckforkeypress == 'r'){
			r = (r>=245)?0:r+=10;
		}else if(charcheckforkeypress == 'g'){
			g = (g>=245)?0:g+=10;
		}else if(charcheckforkeypress == 'b'){
			b = (b>=245)?0:b+=10;
		}else if(charcheckforkeypress == 27)
	      break;
		cout << "Rojo: " << r << "Verde: " << g << "Azul: " << b << endl;
	}
	cvDestroyAllWindows();
	cvReleaseImage(&imagenCamara);
	//cvReleaseCapture(&capturaImagen);

}