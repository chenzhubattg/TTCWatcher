#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block Boxtest
# Generated: Mon Jun 15 22:44:17 2015
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import container
import wx
import thread
from socket import *
import time
from SocketServer import ThreadingTCPServer, BaseRequestHandler 
import struct

class top_block_boxtest(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block Boxtest")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.wxgui_scopesink2_0 = scopesink2.scope_sink_f(
        	self.GetWin(),
        	title="Scope Plot",
        	sample_rate=samp_rate,
        	v_scale=0,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=False,
        	num_inputs=2,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.Add(self.wxgui_scopesink2_0.win)
        self.container_float2float_0 = container.float2float("TTCTask_student")
        (self.container_float2float_0).set_processor_affinity([0])
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_COS_WAVE, 1000, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.container_float2float_0, 0))
        self.connect((self.container_float2float_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.wxgui_scopesink2_0, 0))
        self.connect((self.analog_sig_source_x_0, 0), (self.wxgui_scopesink2_0, 1))



    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.wxgui_scopesink2_0.set_sample_rate(self.samp_rate)

if __name__ == '__main__':
    import ctypes
    import sys
    def tcpset(top):
        HOST = '127.0.0.1'
        PORT = 8010
        BUFSIZE = 1024
        ADDR = (HOST, PORT)
        tcpClientSock = socket(AF_INET, SOCK_STREAM)
	str = 'Try to connect Task server(%s:%d)...' % (HOST,PORT)
	print str
	while True:
		try:
        		tcpClientSock.connect(ADDR)
		except:
			
			print('Unable to connect Task server,try again!...')
			time.sleep(1)
			continue
		break
	str = 'Connect to Task server(%s:%d)' % (HOST,PORT)
        print str
	while True:
            data = tcpClientSock.recv(BUFSIZE)
	    A = struct.unpack("4shh",data)
            print A
            cmd = A[2]
            #if cmd == 4:
            tb.container_float2float_0.Setparam('TTC_Param.xml','container_float2float_0')
        #            top.set_free(A[3])
        tcpClientSock.close()
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block_boxtest()
    tb.container_float2float_0.Setparam('TTC_Param.xml','container_float2float_0')
    tb.Start(True)
    T=(tb,)       
    thread.start_new_thread(tcpset,T)
    tb.Wait()
