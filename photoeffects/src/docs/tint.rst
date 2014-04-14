=======================================
tint
=======================================
Add a tint to the initial image.

.. cpp:function:: int tint(cv::InputArray src, cv::OutputArray dst, const cv::Vec3b &colorTint, float density)

	:param src: Source 8-bit 3-channel(RGB) image.
	:param dst: Destination image of the same size and the same type as **src**.
	:param colorTint: It's a bearing color. All color of the image **src** will be shifted to it.
	:param density: Float value between 0 and 1, defines a range of shift to the colorTint.
	:return: Error code.

The algorithm:

	Calculate new values by this formula:

	- **Rdst = density * Rsrc + (1 - density) * Rtint.**
	- **Gdst = density * Gsrc + (1 - density) * Gtint.**
	- **Bdst = density * Bsrc + (1 - density) * Btint.**

	Where (Rtint, Gtint, Btint) = **colorTint**. 

Example:
	**density** = 10, **colorTint** - |colorTint|

.. |colorTint| image:: colorTint.png

|srcImage| |dstImage|

.. |srcImage| image:: originalForTint.png
	:width: 40%

.. |dstImage| image:: tint.png
	:width: 40%