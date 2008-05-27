Name:  SndObj         
Version: 2.6.6       
Release: 0%{?dist}
Summary: The Sound Object Library - audio processing library       

Group:   Development/Libraries          
License:  GPLv2+      
URL: http://sndobj.sf.net           
Source0: http://downloads.sourceforge.net/sndobj/%{name}-%{version}-linux.tar.gz          
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  python scons swig alsa-lib-devel python-devel jack-audio-connection-kit-devel
%define python_site_dir %(%{__python} -c "from distutils.sysconfig import get_python_lib; print get_python_lib()")

%description
The SndObj library is a class library for general-purpose audio processing, with support
for time and frequency domain processing.

%package devel
Summary: SndObj development files and libraries
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}

%description devel
Headers and libraries for SndObj-based development

%package python
Summary: Python SndObj development files and librariess
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}
Requires: python

%description python
Contains Python language bindings for developing Python
applications with SndObj

%prep
%setup -q

%build
%{_bindir}/scons pythonmodule=1 jack=1 alsa=1 version=%{version} customCCFLAGS="%{optflags}" 

%install
rm -rf $RPM_BUILD_ROOT
scons install prefix=%{_prefix} instdir=%{buildroot}

%post -p /sbin/ldconfig
 
%postun -p /sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/libsndobj.so.%{version}
%doc License.txt

%files devel
%defattr(-,root,root,0755)
%dir %{_includedir}/%{name}
%dir %{_includedir}/rfftw
%{_includedir}/%{name}/*
%{_includedir}/rfftw/*
%{_libdir}/libsndobj.so

%files python
%defattr(-,root,root,-)
%{python_site_dir}/*


%changelog
* Fri May 23 2008 Victor Lazzarini <Victor.Lazzarini@nuim.ie>
  - initial version of this spec 
