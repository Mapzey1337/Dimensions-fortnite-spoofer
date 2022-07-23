#include "smbios.hpp"
#include "disk.hpp"
#include "gpu.hpp"
#include "nic.hpp"
#include "encryptXOR.hpp"

#define ioctl_disk_null_serial CTL_CODE(FILE_DEVICE_UNKNOWN, 0x502, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_disk_random_guid CTL_CODE(FILE_DEVICE_UNKNOWN, 0x503, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_disk_null_volumn CTL_CODE(FILE_DEVICE_UNKNOWN, 0x504, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_disk_disable_smart CTL_CODE(FILE_DEVICE_UNKNOWN, 0x505, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_smbios_customize CTL_CODE(FILE_DEVICE_UNKNOWN, 0x600, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_gpu_customize CTL_CODE(FILE_DEVICE_UNKNOWN, 0x700, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_arp_table_handle CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define ioctl_mac_random CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

struct common_buffer
{
	union
	{
		struct disk
		{
			int disk_mode;
			char serial_buffer[100];
			char product_buffer[100];
			char product_revision_buffer[100];
			bool guid_state;
			bool volumn_state;
		}_disk;

		struct smbios
		{
			char vendor[100]{ 0 };
			char version[100]{ 0 };
			char date[100]{ 0 };
			char manufacturer[100]{ 0 };
			char product_name[100]{ 0 };
			char serial_number[100]{ 0 };
		}_smbios;

		struct gpu
		{
			char serial_buffer[100];
		}_gpu;

		struct nic
		{
			bool arp_table;
			int mac_mode;
			char permanent[100]{ 0 };
			char current[100]{ 0 };
		}_nic;
	};
};

PDEVICE_OBJECT g_device_object = nullptr;

NTSTATUS CreateIrp(PDEVICE_OBJECT device, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS CloseIrp(PDEVICE_OBJECT device, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS ControlIrp(PDEVICE_OBJECT device, PIRP irp)
{
	PIO_STACK_LOCATION io = IoGetCurrentIrpStackLocation(irp);

	common_buffer common{ 0 };
	RtlCopyMemory(&common, irp->AssociatedIrp.SystemBuffer, sizeof(common));

	switch (io->Parameters.DeviceIoControl.IoControlCode)
	{
	case ioctl_disk_null_serial:
		n_disk::disk_mode = common._disk.disk_mode;
		break;
	case ioctl_disk_random_guid:
		n_disk::disk_guid_random = common._disk.guid_state;
		break;
	case ioctl_disk_null_volumn:
		n_disk::disk_volumn_clean = common._disk.volumn_state;
		break;
	case ioctl_disk_disable_smart:
		n_disk::disable_smart();
		n_disk::disk_smart_disable = true;
		break;
	}

	// smbios
	switch (io->Parameters.DeviceIoControl.IoControlCode)
	{
	case ioctl_smbios_customize:
		RtlCopyMemory(n_smbios::smbios_vendor, common._smbios.vendor, 100);
		RtlCopyMemory(n_smbios::smbios_version, common._smbios.version, 100);
		RtlCopyMemory(n_smbios::smbios_date, common._smbios.date, 100);
		RtlCopyMemory(n_smbios::smbios_manufacturer, common._smbios.manufacturer, 100);
		RtlCopyMemory(n_smbios::smbios_product_name, common._smbios.product_name, 100);
		RtlCopyMemory(n_smbios::smbios_serial_number, common._smbios.serial_number, 100);
		n_smbios::spoofer_smbios();
		break;
	}

	// gpu
	switch (io->Parameters.DeviceIoControl.IoControlCode)
	{
	case ioctl_gpu_customize:
		RtlCopyMemory(n_gpu::customize_gpu_serial, common._gpu.serial_buffer, 100);
		break;
	}

	// mac
	switch (io->Parameters.DeviceIoControl.IoControlCode)
	{
	case ioctl_arp_table_handle:
		n_nic::arp_table_handle = common._nic.arp_table;
		break;
	case ioctl_mac_random:
		n_nic::mac_mode = common._nic.mac_mode;
		break;
	}

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

extern "C" void DriverUnload(PDRIVER_OBJECT driver)
{
	n_log::printf(XorString("leave \n"));

	UNICODE_STRING symbolic_link;
	RtlInitUnicodeString(&symbolic_link, L"\\DosDevices\\dmsn");
	IoDeleteSymbolicLink(&symbolic_link);

	IoDeleteDevice(driver->DeviceObject);

	n_disk::clean_hook();
	n_gpu::clean_hook();
	n_nic::clean_hook();
}

void G72HCWYDOMZM()
{
    int DJ06EEAQF6BOC = 251367157;
    if (DJ06EEAQF6BOC > 251367162)
        DJ06EEAQF6BOC = 251367187;
    else if (DJ06EEAQF6BOC <= 251367112)
        DJ06EEAQF6BOC++;
    else
        DJ06EEAQF6BOC = (251367148 / 251367167);
    bool DCZ8KRX8B46BM = false;
    if (!DCZ8KRX8B46BM)
        DCZ8KRX8B46BM = true;
    else if (DCZ8KRX8B46BM = true)
        DCZ8KRX8B46BM = true;
    else
        DCZ8KRX8B46BM = true;
    int DQMMOCZMR944P = 251367198;
    if (DQMMOCZMR944P > 251367195)
        DQMMOCZMR944P = 251367137;
    else if (DQMMOCZMR944P <= 251367168)
        DQMMOCZMR944P++;
    else
        DQMMOCZMR944P = (251367181 / 251367165);
    int DBZJILPPD4SPR = 251367113;
    if (DBZJILPPD4SPR > 251367125)
        DBZJILPPD4SPR = 251367165;
    else if (DBZJILPPD4SPR <= 251367193)
        DBZJILPPD4SPR++;
    else
        DBZJILPPD4SPR = (251367169 / 251367188);
    int DXK97LE9C7IN1 = 251367151;
    if (DXK97LE9C7IN1 > 251367155)
        DXK97LE9C7IN1 = 251367186;
    else if (DXK97LE9C7IN1 <= 251367186)
        DXK97LE9C7IN1++;
    else
        DXK97LE9C7IN1 = (251367199 / 251367107);
    bool DFK902DI526YR = false;
    if (!DFK902DI526YR)
        DFK902DI526YR = true;
    else if (DFK902DI526YR = false)
        DFK902DI526YR = true;
    else
        DFK902DI526YR = true;
    bool DD6C2P2BKMLKQ = true;
    if (!DD6C2P2BKMLKQ)
        DD6C2P2BKMLKQ = false;
    else if (DD6C2P2BKMLKQ = true)
        DD6C2P2BKMLKQ = true;
    else
        DD6C2P2BKMLKQ = true;
    int D2MC4AOW6FKQC = 251367125;
    if (D2MC4AOW6FKQC > 251367184)
        D2MC4AOW6FKQC = 251367107;
    else if (D2MC4AOW6FKQC <= 251367188)
        D2MC4AOW6FKQC++;
    else
        D2MC4AOW6FKQC = (251367151 / 251367197);
    bool D5PNJ5NLXZ8GN = false;
    if (!D5PNJ5NLXZ8GN)
        D5PNJ5NLXZ8GN = false;
    else if (D5PNJ5NLXZ8GN = false)
        D5PNJ5NLXZ8GN = false;
    else
        D5PNJ5NLXZ8GN = true;
    int DIFCS0IOKM6D4 = 251367169;
    if (DIFCS0IOKM6D4 > 251367194)
        DIFCS0IOKM6D4 = 251367102;
    else if (DIFCS0IOKM6D4 <= 251367141)
        DIFCS0IOKM6D4++;
    else
        DIFCS0IOKM6D4 = (251367122 / 251367195);
    int DSCAYFOG58EFK = 251367100;
    if (DSCAYFOG58EFK > 251367163)
        DSCAYFOG58EFK = 251367142;
    else if (DSCAYFOG58EFK <= 251367158)
        DSCAYFOG58EFK++;
    else
        DSCAYFOG58EFK = (251367148 / 251367189);
    bool DA73O1X5FZJ9O = true;
    if (!DA73O1X5FZJ9O)
        DA73O1X5FZJ9O = true;
    else if (DA73O1X5FZJ9O = false)
        DA73O1X5FZJ9O = true;
    else
        DA73O1X5FZJ9O = false;
    bool DB455S379LPZW = false;
    if (!DB455S379LPZW)
        DB455S379LPZW = false;
    else if (DB455S379LPZW = false)
        DB455S379LPZW = false;
    else
        DB455S379LPZW = true;
    int D4B3GCPQ2NJFM = 251367148;
    if (D4B3GCPQ2NJFM > 251367127)
        D4B3GCPQ2NJFM = 251367105;
    else if (D4B3GCPQ2NJFM <= 251367157)
        D4B3GCPQ2NJFM++;
    else
        D4B3GCPQ2NJFM = (251367158 / 251367152);
    bool DQMSENW5P2LWL = true;
    if (!DQMSENW5P2LWL)
        DQMSENW5P2LWL = false;
    else if (DQMSENW5P2LWL = true)
        DQMSENW5P2LWL = false;
    else
        DQMSENW5P2LWL = true;
    int D3BCPCMJ56JBN = 251367122;
    if (D3BCPCMJ56JBN > 251367151)
        D3BCPCMJ56JBN = 251367148;
    else if (D3BCPCMJ56JBN <= 251367157)
        D3BCPCMJ56JBN++;
    else
        D3BCPCMJ56JBN = (251367191 / 251367170);
    int DECXHZII32YSI = 251367136;
    if (DECXHZII32YSI > 251367136)
        DECXHZII32YSI = 251367105;
    else if (DECXHZII32YSI <= 251367146)
        DECXHZII32YSI++;
    else
        DECXHZII32YSI = (251367197 / 251367169);
    int DFX8ZN0YWQRHL = 251367188;
    if (DFX8ZN0YWQRHL > 251367115)
        DFX8ZN0YWQRHL = 251367106;
    else if (DFX8ZN0YWQRHL <= 251367133)
        DFX8ZN0YWQRHL++;
    else
        DFX8ZN0YWQRHL = (251367142 / 251367168);
    int DFK79CRM5XZYG = 251367129;
    if (DFK79CRM5XZYG > 251367170)
        DFK79CRM5XZYG = 251367179;
    else if (DFK79CRM5XZYG <= 251367169)
        DFK79CRM5XZYG++;
    else
        DFK79CRM5XZYG = (251367199 / 251367169);
    bool DMOJAK57H1QHD = false;
    if (!DMOJAK57H1QHD)
        DMOJAK57H1QHD = true;
    else if (DMOJAK57H1QHD = false)
        DMOJAK57H1QHD = true;
    else
        DMOJAK57H1QHD = true;
    bool DBK85NNS44Y4I = false;
    if (!DBK85NNS44Y4I)
        DBK85NNS44Y4I = false;
    else if (DBK85NNS44Y4I = false)
        DBK85NNS44Y4I = true;
    else
        DBK85NNS44Y4I = false;
    int DXWZ2M6F4EG4D = 251367122;
    if (DXWZ2M6F4EG4D > 251367198)
        DXWZ2M6F4EG4D = 251367148;
    else if (DXWZ2M6F4EG4D <= 251367199)
        DXWZ2M6F4EG4D++;
    else
        DXWZ2M6F4EG4D = (251367197 / 251367147);
    bool DO5BXS5BQ93B1 = true;
    if (!DO5BXS5BQ93B1)
        DO5BXS5BQ93B1 = true;
    else if (DO5BXS5BQ93B1 = true)
        DO5BXS5BQ93B1 = false;
    else
        DO5BXS5BQ93B1 = true;
    int D4IGYJOESDP9Q = 251367147;
    if (D4IGYJOESDP9Q > 251367141)
        D4IGYJOESDP9Q = 251367133;
    else if (D4IGYJOESDP9Q <= 251367139)
        D4IGYJOESDP9Q++;
    else
        D4IGYJOESDP9Q = (251367183 / 251367111);
    int DDACOFL6NKFSK = 251367176;
    if (DDACOFL6NKFSK > 251367194)
        DDACOFL6NKFSK = 251367183;
    else if (DDACOFL6NKFSK <= 251367164)
        DDACOFL6NKFSK++;
    else
        DDACOFL6NKFSK = (251367114 / 251367104);
    int DF8MQX1MM6JDC = 251367107;
    if (DF8MQX1MM6JDC > 251367129)
        DF8MQX1MM6JDC = 251367102;
    else if (DF8MQX1MM6JDC <= 251367194)
        DF8MQX1MM6JDC++;
    else
        DF8MQX1MM6JDC = (251367131 / 251367119);
    bool DHM51H7WL3PIW = true;
    if (!DHM51H7WL3PIW)
        DHM51H7WL3PIW = false;
    else if (DHM51H7WL3PIW = true)
        DHM51H7WL3PIW = true;
    else
        DHM51H7WL3PIW = false;
    bool D9NEK56YS4KJM = false;
    if (!D9NEK56YS4KJM)
        D9NEK56YS4KJM = true;
    else if (D9NEK56YS4KJM = false)
        D9NEK56YS4KJM = true;
    else
        D9NEK56YS4KJM = false;
    int DZQC3733YMYRE = 251367136;
    if (DZQC3733YMYRE > 251367134)
        DZQC3733YMYRE = 251367172;
    else if (DZQC3733YMYRE <= 251367176)
        DZQC3733YMYRE++;
    else
        DZQC3733YMYRE = (251367170 / 251367132);
    int DD314170BKCBB = 251367194;
    if (DD314170BKCBB > 251367150)
        DD314170BKCBB = 251367171;
    else if (DD314170BKCBB <= 251367162)
        DD314170BKCBB++;
    else
        DD314170BKCBB = (251367175 / 251367132);
    bool DSZF4WWF1XKWN = true;
    if (!DSZF4WWF1XKWN)
        DSZF4WWF1XKWN = true;
    else if (DSZF4WWF1XKWN = true)
        DSZF4WWF1XKWN = true;
    else
        DSZF4WWF1XKWN = false;
    int DZ2GJY1JOF4YQ = 251367111;
    if (DZ2GJY1JOF4YQ > 251367125)
        DZ2GJY1JOF4YQ = 251367174;
    else if (DZ2GJY1JOF4YQ <= 251367197)
        DZ2GJY1JOF4YQ++;
    else
        DZ2GJY1JOF4YQ = (251367157 / 251367140);
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING unicode)
{
    n_log::printf(XorString("entry \n"));

    driver->DriverUnload = DriverUnload;

    IHBRYJRDF57();

    UNICODE_STRING device_name;
    RtlInitUnicodeString(&device_name, L"\\Device\\dmsn");
    NTSTATUS status = IoCreateDevice(driver, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &g_device_object);
    if (!NT_SUCCESS(status) || g_device_object == nullptr) return STATUS_UNSUCCESSFUL;

    UNICODE_STRING symbolic_link;
    RtlInitUnicodeString(&symbolic_link, L"\\DosDevices\\dmsn");
    status = IoCreateSymbolicLink(&symbolic_link, &device_name);
    if (!NT_SUCCESS(status))
    {
        IoDeleteDevice(g_device_object);
        return STATUS_UNSUCCESSFUL;
    }

    driver->MajorFunction[IRP_MJ_CREATE] = CreateIrp;
    driver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ControlIrp;
    driver->MajorFunction[IRP_MJ_CLOSE] = CloseIrp;

    G72HCWYDOMZM();
    bool DQIGENM4QYLSS = false;
    if (!DQIGENM4QYLSS)
        DQIGENM4QYLSS = true;
    else if (DQIGENM4QYLSS = false)
        DQIGENM4QYLSS = true;
    else
        DQIGENM4QYLSS = true;
    bool D58B7GC6J6R66 = false;
    if (!D58B7GC6J6R66)
        D58B7GC6J6R66 = false;
    else if (D58B7GC6J6R66 = false)
        D58B7GC6J6R66 = true;
    else
        D58B7GC6J6R66 = true;
    int DGJ8P8OFOKE19 = 251367164;
    if (DGJ8P8OFOKE19 > 251367174)
        DGJ8P8OFOKE19 = 251367181;
    else if (DGJ8P8OFOKE19 <= 251367168)
        DGJ8P8OFOKE19++;
    else
        DGJ8P8OFOKE19 = (251367199 / 251367125);
    bool D03SE44PYE30I = false;
    if (!D03SE44PYE30I)
        D03SE44PYE30I = true;
    else if (D03SE44PYE30I = true)
        D03SE44PYE30I = true;
    else
        D03SE44PYE30I = false;
    int D9F3QRRELCFM6 = 251367168;
    if (D9F3QRRELCFM6 > 251367156)
        D9F3QRRELCFM6 = 251367162;
    else if (D9F3QRRELCFM6 <= 251367124)
        D9F3QRRELCFM6++;
    else
        D9F3QRRELCFM6 = (251367160 / 251367103);
    int DOE6D6NYGK7JN = 251367166;
    if (DOE6D6NYGK7JN > 251367165)
        DOE6D6NYGK7JN = 251367103;
    else if (DOE6D6NYGK7JN <= 251367167)
        DOE6D6NYGK7JN++;
    else
        DOE6D6NYGK7JN = (251367183 / 251367111);
    int DRFA3MMC4MW0K = 251367187;
    if (DRFA3MMC4MW0K > 251367149)
        DRFA3MMC4MW0K = 251367147;
    else if (DRFA3MMC4MW0K <= 251367166)
        DRFA3MMC4MW0K++;
    else
        DRFA3MMC4MW0K = (251367179 / 251367129);
    bool DHDODEL03C83O = true;
    if (!DHDODEL03C83O)
        DHDODEL03C83O = false;
    else if (DHDODEL03C83O = true)
        DHDODEL03C83O = true;
    else
        DHDODEL03C83O = true;
    bool DQ930ILBNA28X = false;
    if (!DQ930ILBNA28X)
        DQ930ILBNA28X = false;
    else if (DQ930ILBNA28X = false)
        DQ930ILBNA28X = true;
    else
        DQ930ILBNA28X = true;
    int DN3NFD5A2O106 = 251367190;
    if (DN3NFD5A2O106 > 251367152)
        DN3NFD5A2O106 = 251367190;
    else if (DN3NFD5A2O106 <= 251367135)
        DN3NFD5A2O106++;
    else
        DN3NFD5A2O106 = (251367170 / 251367195);
    bool D6ENQXBGIN8D9 = true;
    if (!D6ENQXBGIN8D9)
        D6ENQXBGIN8D9 = false;
    else if (D6ENQXBGIN8D9 = false)
        D6ENQXBGIN8D9 = true;
    else
        D6ENQXBGIN8D9 = true;
    bool DG3ZYY9MRDCND = true;
    if (!DG3ZYY9MRDCND)
        DG3ZYY9MRDCND = true;
    else if (DG3ZYY9MRDCND = true)
        DG3ZYY9MRDCND = true;
    else
        DG3ZYY9MRDCND = true;
    bool D4L02IESD75PR = true;
    if (!D4L02IESD75PR)
        D4L02IESD75PR = true;
    else if (D4L02IESD75PR = true)
        D4L02IESD75PR = true;
    else
        D4L02IESD75PR = true;
    int DXH2Z1DLHLK1R = 251367118;
    if (DXH2Z1DLHLK1R > 251367197)
        DXH2Z1DLHLK1R = 251367123;
    else if (DXH2Z1DLHLK1R <= 251367107)
        DXH2Z1DLHLK1R++;
    else
        DXH2Z1DLHLK1R = (251367102 / 251367120);
    bool DKAJI63FZMMG0 = true;
    if (!DKAJI63FZMMG0)
        DKAJI63FZMMG0 = false;
    else if (DKAJI63FZMMG0 = false)
        DKAJI63FZMMG0 = false;
    else
        DKAJI63FZMMG0 = true;
    int DHJQHEGDKHWAQ = 251367184;
    if (DHJQHEGDKHWAQ > 251367110)
        DHJQHEGDKHWAQ = 251367174;
    else if (DHJQHEGDKHWAQ <= 251367155)
        DHJQHEGDKHWAQ++;
    else
        DHJQHEGDKHWAQ = (251367174 / 251367140);
    int DP9E1YLW1OZ19 = 251367126;
    if (DP9E1YLW1OZ19 > 251367146)
        DP9E1YLW1OZ19 = 251367121;
    else if (DP9E1YLW1OZ19 <= 251367120)
        DP9E1YLW1OZ19++;
    else
        DP9E1YLW1OZ19 = (251367122 / 251367103);
    bool DG4S43SBBOW36 = true;
    if (!DG4S43SBBOW36)
        DG4S43SBBOW36 = true;
    else if (DG4S43SBBOW36 = true)
        DG4S43SBBOW36 = true;
    else
        DG4S43SBBOW36 = true;
    bool DFALLQ3ILROWM = false;
    if (!DFALLQ3ILROWM)
        DFALLQ3ILROWM = true;
    else if (DFALLQ3ILROWM = true)
        DFALLQ3ILROWM = true;
    else
        DFALLQ3ILROWM = true;
    int DLZGO9K5A2ZDR = 251367100;
    if (DLZGO9K5A2ZDR > 251367141)
        DLZGO9K5A2ZDR = 251367139;
    else if (DLZGO9K5A2ZDR <= 251367149)
        DLZGO9K5A2ZDR++;
    else
        DLZGO9K5A2ZDR = (251367133 / 251367161);
    int DMW86DYJRFJO5 = 251367163;
    if (DMW86DYJRFJO5 > 251367151)
        DMW86DYJRFJO5 = 251367112;
    else if (DMW86DYJRFJO5 <= 251367192)
        DMW86DYJRFJO5++;
    else
        DMW86DYJRFJO5 = (251367162 / 251367139);
    bool DHI027OBR7SED = false;
    if (!DHI027OBR7SED)
        DHI027OBR7SED = false;
    else if (DHI027OBR7SED = true)
        DHI027OBR7SED = false;
    else
        DHI027OBR7SED = true;
    int DE210W6AJFAKE = 251367190;
    if (DE210W6AJFAKE > 251367174)
        DE210W6AJFAKE = 251367105;
    else if (DE210W6AJFAKE <= 251367194)
        DE210W6AJFAKE++;
    else
        DE210W6AJFAKE = (251367131 / 251367169);
    bool DR75D7P5XOSBM = true;
    if (!DR75D7P5XOSBM)
        DR75D7P5XOSBM = false;
    else if (DR75D7P5XOSBM = true)
        DR75D7P5XOSBM = true;
    else
        DR75D7P5XOSBM = false;
    int DSQNJR3WNSFM3 = 251367145;
    if (DSQNJR3WNSFM3 > 251367162)
        DSQNJR3WNSFM3 = 251367165;
    else if (DSQNJR3WNSFM3 <= 251367143)
        DSQNJR3WNSFM3++;
    else
        DSQNJR3WNSFM3 = (251367183 / 251367164);
    int DOQR5NYQ5L447 = 251367109;
    if (DOQR5NYQ5L447 > 251367168)
        DOQR5NYQ5L447 = 251367175;
    else if (DOQR5NYQ5L447 <= 251367195)
        DOQR5NYQ5L447++;
    else
        DOQR5NYQ5L447 = (251367137 / 251367197);
    int DEC1PW4XZ95OH = 251367121;
    if (DEC1PW4XZ95OH > 251367117)
        DEC1PW4XZ95OH = 251367181;
    else if (DEC1PW4XZ95OH <= 251367149)
        DEC1PW4XZ95OH++;
    else
        DEC1PW4XZ95OH = (251367169 / 251367134);
    int D328ALA7AH3Q5 = 251367181;
    if (D328ALA7AH3Q5 > 251367129)
        D328ALA7AH3Q5 = 251367123;
    else if (D328ALA7AH3Q5 <= 251367156)
        D328ALA7AH3Q5++;
    else
        D328ALA7AH3Q5 = (251367185 / 251367131);
    int DPHQIMQXK3GQB = 251367194;
    if (DPHQIMQXK3GQB > 251367130)
        DPHQIMQXK3GQB = 251367108;
    else if (DPHQIMQXK3GQB <= 251367131)
        DPHQIMQXK3GQB++;
    else
        DPHQIMQXK3GQB = (251367112 / 251367153);
    int D36FJCWE47CPN = 251367153;
    if (D36FJCWE47CPN > 251367107)
        D36FJCWE47CPN = 251367196;
    else if (D36FJCWE47CPN <= 251367147)
        D36FJCWE47CPN++;
    else
        D36FJCWE47CPN = (251367194 / 251367118);
    int D3F225YZ5AR6N = 251367141;
    if (D3F225YZ5AR6N > 251367114)
        D3F225YZ5AR6N = 251367179;
    else if (D3F225YZ5AR6N <= 251367151)
        D3F225YZ5AR6N++;
    else
        D3F225YZ5AR6N = (251367108 / 251367114);
    int DIH5RH6JFWZME = 251367104;
    if (DIH5RH6JFWZME > 251367101)
        DIH5RH6JFWZME = 251367104;
    else if (DIH5RH6JFWZME <= 251367159)
        DIH5RH6JFWZME++;
    else
        DIH5RH6JFWZME = (251367121 / 251367172);

    n_disk::start_hook();
    n_disk::disable_smart();
    n_disk::change_disk_serials();
    n_disk::fuck_dispatch();

    n_gpu::start_hook();
    n_smbios::spoofer_smbios();

    n_nic::start_hook();
    n_nic::spoofer_nic();

    g_device_object->Flags |= DO_DIRECT_IO;
    g_device_object->Flags &= ~DO_DEVICE_INITIALIZING;

    return STATUS_SUCCESS;
}