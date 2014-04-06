=======================================
glow
=======================================
Applies glow effect to the initial image

.. cpp:function:: int glow(cv::InputArray src, cv::OutputArray dst, float sigma, float intensity = 0.0f)

    :param src: RGB image.
    :param dst: Destination image of the same size and the same type as **src**.
    :param sigma: Gaussian kernel standard deviation, must be positive real number
    :param intensity:  Effect intensity, must be real number from 0.0 to 1.0
    :return: Error code.

The algorithm:

#. Create the copy of the source image
#. Apply Gaussian blur for this copy with deviation equal **sigma**
#. Create new 3-channel image, each channel of the matrix calculates by the following formula:

    .. math::

        \begin{equation}
            C = \begin{cases}
                2 * A * B, & \text{if $B <= 0.5$}\\
                1 - 2 * (1 - A) * (1 - B), & \text{otherwise}
            \end{cases}
        \end{equation}
    
where :math:`A` is the pixel's tonal value that lies in the blurred image, :math:`B` is the pixel's tonal value that lies in the source image, :math:`C` is the tonal value of the blended pixel.

4. Create new 3-channel image, each channel of the matrix calculates by the following formula:

    .. math::

        \begin{equation}
            C = intensity * A + (1 - intensity) * B 
        \end{equation} 

where :math:`A` is the pixel's tonal value that lies in the previous blended image, :math:`B` is the pixel's tonal value that lies in the source image, :math:`C` is the tonal value of the blended pixel.

5. Save previous image as RGB image

Example:

|src| |dst|

.. |src| image:: rose.jpg
    :width: 40%

.. |dst| image:: glow.jpg
    :width: 40%